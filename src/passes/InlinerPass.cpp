#include "InlinerPass.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/Transforms/Utils/Cloning.h>

InlinerPass::InlinerPass(bool InlineIntrinsicFunctions)
    : InlineIntrinsicFunctions(InlineIntrinsicFunctions)
{
}

llvm::PreservedAnalyses InlinerPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    bool Modified{};
    // Inline untill there's nothing to inline.
    //
    llvm::SmallVector<llvm::CallInst*> FunctionCalls;
    do
    {
        FunctionCalls.clear();
        for (auto &Instruction : llvm::instructions(Function))
        {
            if (auto Call = dyn_cast<llvm::CallInst>(&Instruction))
            {
                const auto FunctionName = Call->getCalledFunction()->getName();
                if (FunctionName.starts_with("__remill_read") ||
                    FunctionName.starts_with("__remill_write"))
                {
                    if (InlineIntrinsicFunctions)
                    {
                        FunctionCalls.push_back(Call);
                    }
                }
                if (Call->getCalledFunction()->hasFnAttribute(llvm::Attribute::AlwaysInline))
                {
                    FunctionCalls.push_back(Call);
                }
            }
        }

        for (auto Call : FunctionCalls)
        {
            llvm::InlineFunctionInfo IFI;
            llvm::InlineFunction(*Call, IFI);
        }

        Modified |= !FunctionCalls.empty();
    } while (!FunctionCalls.empty());

    return Modified ? llvm::PreservedAnalyses::none() : llvm::PreservedAnalyses::all();
}
