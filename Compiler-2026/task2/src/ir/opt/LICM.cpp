#include "ir/opt/LICM.hpp"

#include <vector>

bool LICMPass::isHoistableBinary(const Instruction *I) {
    if (!I || !dynamic_cast<const BinaryInst *>(I)) return false;
    switch (I->instType) {
    case Instruction::ADD:
    case Instruction::SUB:
    case Instruction::MUL:
    case Instruction::SDIV:
    case Instruction::UDIV:
    case Instruction::SREM:
    case Instruction::UREM:
    case Instruction::AND:
    case Instruction::OR:
    case Instruction::XOR:
    case Instruction::SHL:
    case Instruction::LSHR:
    case Instruction::ASHR:
    case Instruction::ICMP:
        return true;
    default:
        return false;
    }
}

bool LICMPass::isSpeculatableBinary(const Instruction *I) {
    if (!I) return false;
    switch (I->instType) {
    case Instruction::SDIV:
    case Instruction::UDIV:
    case Instruction::SREM:
    case Instruction::UREM:
        return false;
    default:
        return true;
    }
}

bool LICMPass::allOperandsLoopInvariant(BinaryInst *BI, Loop *L) {
    Value *LHS = nullptr;
    Value *RHS = nullptr;
    if (!BI->getOperands(LHS, RHS)) return false;
    return LoopInfo::isLoopInvariant(LHS, L) &&
           LoopInfo::isLoopInvariant(RHS, L);
}

bool LICMPass::isGuaranteedToExecute(BasicBlock *BB, Loop *L,
                                     DominatorTree &DT) {
    auto ExitBlocks = L->getExitBlocks();
    if (ExitBlocks.empty()) return false;
    for (BasicBlock *Exit : ExitBlocks) {
        if (!Exit || !DT.dominates(BB, Exit)) return false;
    }
    return true;
}

bool LICMPass::hoistBlock(BasicBlock *BB, BasicBlock *PreHeader, Loop *L,
                          DominatorTree &DT) {
    std::vector<Instruction *> Instructions;
    for (Instruction *I : *BB) {
        if (I) Instructions.push_back(I);
    }

    bool Changed = false;
    for (Instruction *I : Instructions) {
        if (!isHoistableBinary(I)) continue;
        if (!isSpeculatableBinary(I) && !isGuaranteedToExecute(BB, L, DT))
            continue;
        auto *BI = static_cast<BinaryInst *>(I);
        if (!allOperandsLoopInvariant(BI, L)) continue;
        I->eraseFromParent();
        PreHeader->insertBeforeTerminator(I);
        Changed = true;
    }
    return Changed;
}

bool LICMPass::hoistLoop(Loop *L, DominatorTree &DT) {
    if (!L) return false;
    BasicBlock *PreHeader = nullptr;
    BasicBlock *Latch = nullptr;
    if (!L->getLoopSimplifyForm(PreHeader, Latch) || !PreHeader) return false;

    bool AnyChanged = false;
    for (int Round = 0; Round < 8; ++Round) {
        bool RoundChanged = false;
        for (BasicBlock *BB : L->getBlocksInRPO()) {
            if (!BB || BB == PreHeader) continue;
            if (hoistBlock(BB, PreHeader, L, DT)) RoundChanged = true;
        }
        if (!RoundChanged) break;
        AnyChanged = true;
    }
    return AnyChanged;
}

PassResult LICMPass::run(Function &F, FunctionAnalysisPassManager &FAM) {
    auto &DT = FAM.getResult<DominantAnalysis>(F);
    auto &LI = FAM.getResult<LoopAnalysis>(F);

    bool Changed = false;
    for (Loop *L : LI.getLoopsInPostOrder()) {
        if (hoistLoop(L, DT)) Changed = true;
    }
    if (!Changed) return PassResult::unchanged();

    PreservationStatus PA;
    PA.keep<DominantAnalysis>();
    PA.keep<LoopAnalysis>();
    return PassResult::changed(std::move(PA));
}
