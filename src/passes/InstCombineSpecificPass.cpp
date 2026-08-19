#include "InstCombineSpecificPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/PatternMatch.h>

llvm::PreservedAnalyses InstCombineSpecificPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    // %7 = add i64 %vs, -56
    // %8 = add i64 %vs, -24
    // %9 = add i64 %arg0, 56
    // %10 = sub i64 %9, %vs
    // %11 = getelementptr i8, ptr %memory, i64 %10
    // %12 = getelementptr i8, ptr %11, i64 %8
    // %13 = load i8, ptr %12, align 1

    // %14 = getelementptr i8, ptr %memory, i64 %8
    // store i8 %13, ptr %14, align 1
    // %15 = add i64 %vs, -23
    // %16 = getelementptr i8, ptr %11, i64 %15
    // %17 = load i8, ptr %16, align 1
    llvm::IRBuilder<> IR(Function.getContext());

    llvm::Value* Arg1 = nullptr;
    llvm::Value* Arg2 = nullptr;
    llvm::Value* Arg3 = nullptr;
    llvm::Value* Arg4 = nullptr;

    llvm::ConstantInt* Constant1 = nullptr;
    llvm::ConstantInt* Constant2 = nullptr;

    auto Pattern = llvm::PatternMatch::m_GEP(
        llvm::PatternMatch::m_GEP(
            llvm::PatternMatch::m_Value(Arg1),
            llvm::PatternMatch::m_Sub(
                llvm::PatternMatch::m_Add(
                    llvm::PatternMatch::m_Value(Arg2),
                    llvm::PatternMatch::m_ConstantInt(Constant1)
                ),
                llvm::PatternMatch::m_Value(Arg3)
            )
        ),
        llvm::PatternMatch::m_Add(
            llvm::PatternMatch::m_Value(Arg4),
            llvm::PatternMatch::m_ConstantInt(Constant2)
        )
    );

    bool Modified = false;
    for (auto& Instruction : llvm::instructions(Function))
    {
        if (llvm::PatternMatch::match(&Instruction, Pattern))
        {
            fassert(Arg4 == Arg3);
            fassert(Arg3 != Arg2);
            fassert(Arg3 != Arg1);
            fassert(Arg2 != Arg1);

            IR.SetInsertPoint(&Instruction);
            Instruction.setOperand(0, Arg1);
            Instruction.setOperand(1, IR.CreateAdd(Arg2, IR.CreateAdd(Constant1, Constant2)));
            Modified = true;
        }
    }

    return Modified
        ? llvm::PreservedAnalyses::none()
        : llvm::PreservedAnalyses::all();
}
