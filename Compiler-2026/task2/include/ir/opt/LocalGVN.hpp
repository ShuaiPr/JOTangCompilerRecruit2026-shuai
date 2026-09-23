#pragma once

#include "ir/opt/NewPassManager.hpp"

#include <cstddef>
#include <unordered_map>

//教学任务：基于局部值编号，消除单个基本块内的重复整数纯计算。
//基础实现利用Mem2Reg生成的SSA和Use/User接口，不需要额外分析pass。
//基础范围：整数加减乘、按位与/或/异或、整数比较；支持交换律和级联重复。
// 
//1. 作用域限定在单个基本块内：按块内指令的线性顺序扫描，同一表达式键第一次
//   出现的指令一定是先行者 ，它在本块内位于重复计算之前，因此不只支配
//   本块的后半部分，也支配本块所支配的其它区域，直接把重复指令的全部使用改绑到
//   先行者即可，不需要构造和使用支配树。
//2.  <操作码, 规范化后的左操作数, 规范化后的右操作数>：
//   - 交换律操作码（ADD/MUL/AND/OR/XOR/E/NE）按操作数地址排序，使 a op b 与
//     b op a 落到同一个键；
//   - 非交换的比较操作码（G/GE/L/LE）在交换操作数的同时用reversePredicate把
//     谓词换成等价谓词，使 a < b 与 b > a 落到同一个键；
//   - 其余操作码保持原有操作数顺序。
//3.  命中重复时先replaceAllUsesWith再删除重复指令 
class LocalGVNPass : public PassDescriptor<LocalGVNPass> {
public:
    PassResult run(Function &F, FunctionAnalysisPassManager &FAM);

private: 
    struct ExpressionKey { 
        BinaryInst::Operation Op; 
        Value *LHS; 
        Value *RHS; 
        bool operator==(const ExpressionKey &Other) const;
    };
 
    struct ExpressionKeyHash {
        std::size_t operator()(const ExpressionKey &Key) const;
    };
 
    using ValueNumberTable =
        std::unordered_map<ExpressionKey, Value *, ExpressionKeyHash>;
 
    static bool isCSEableBinary(const Instruction *I); 
    static bool buildExpressionKey(BinaryInst *BI, ExpressionKey &Key); 
    static bool eliminateRedundantComputations(BasicBlock &BB);
};
