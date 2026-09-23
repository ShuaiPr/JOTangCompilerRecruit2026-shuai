#include "ir/opt/LocalGVN.hpp"

#include "ir/analysis/Dominant.hpp"
#include "ir/analysis/LoopInfo.hpp"

#include <functional>
#include <utility>
#include <vector>
 
bool LocalGVNPass::ExpressionKey::operator==(const ExpressionKey &Other) const {
    return Op == Other.Op && LHS == Other.LHS && RHS == Other.RHS;
}

//表达式键哈希：操作码与两个操作数指针按黄金比例常量逐项混合。
std::size_t
LocalGVNPass::ExpressionKeyHash::operator()(const ExpressionKey &Key) const {
    constexpr std::size_t GoldenRatio = 0x9e3779b97f4a7c15ULL;
    std::size_t Hash = std::hash<unsigned>{}(static_cast<unsigned>(Key.Op));
    Hash ^= std::hash<const Value *>{}(Key.LHS) + GoldenRatio + (Hash << 6) +
            (Hash >> 2);
    Hash ^= std::hash<const Value *>{}(Key.RHS) + GoldenRatio + (Hash << 6) +
            (Hash >> 2);
    return Hash;
}
 
bool LocalGVNPass::isCSEableBinary(const Instruction *I) {
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
 
bool LocalGVNPass::buildExpressionKey(BinaryInst *BI, ExpressionKey &Key) {
    Value *LHS = nullptr;
    Value *RHS = nullptr;
    if (!BI->getOperands(LHS, RHS)) return false;

    BinaryInst::Operation Op = BI->getOp(); 
    const auto PointerLess = std::less<const Value *>{};
    if (BinaryInst::isCommutativeOp(Op)) { 
        if (PointerLess(RHS, LHS)) std::swap(LHS, RHS);
    } else if (BinaryInst::isCompareOp(Op)) { 
        if (PointerLess(RHS, LHS)) {
            std::swap(LHS, RHS);
            Op = BinaryInst::reversePredicate(Op);
        }
    }
    Key = ExpressionKey{Op, LHS, RHS};
    return true;
}
 
bool LocalGVNPass::eliminateRedundantComputations(BasicBlock &BB) { 
    std::vector<Instruction *> Snapshot;
    for (Instruction *I : BB) {
        if (I) Snapshot.push_back(I);
    }

    ValueNumberTable Table;
    bool Changed = false;
    for (Instruction *I : Snapshot) {
        if (!isCSEableBinary(I)) continue;
        auto *BI = static_cast<BinaryInst *>(I);

        ExpressionKey Key{};
        if (!buildExpressionKey(BI, Key)) continue;

        auto It = Table.find(Key);
        if (It == Table.end()) { 
            Table.emplace(Key, BI);
            continue;
        }

        Value *Leader = It->second;
        if (Leader == BI) continue; 
        BI->replaceAllUsesWith(Leader);
        delete BI;
        Changed = true;
    }
    return Changed;
}

PassResult LocalGVNPass::run(Function &F, FunctionAnalysisPassManager &FAM) { 
    (void)FAM;

    bool Changed = false;
    for (BasicBlock *BB : F) {
        if (BB && eliminateRedundantComputations(*BB)) Changed = true;
    }
    if (!Changed) return PassResult::unchanged();
 
    PreservationStatus PA;
    PA.keep<DominantAnalysis>();
    PA.keep<LoopAnalysis>();
    return PassResult::changed(std::move(PA));
}
