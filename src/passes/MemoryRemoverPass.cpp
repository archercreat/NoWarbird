#include "passes/MemoryRemoverPass.hpp"
#include "logger.hpp"
#include "utils.hpp"

#include <llvm/IR/IRBuilder.h>

/// This pass converts *(DWORD*)(Memory + offset) = value to *(DWORD*)(offset) = value
///
llvm::PreservedAnalyses MemoryRemoverPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    auto MemoryArgument = GetFunctionArgument(&Function, MainFunctionArgument::Memory);

    if (MemoryArgument->getNumUses() == 0)
    {
        return llvm::PreservedAnalyses::all();
    }

    llvm::IRBuilder<> IR(Function.getContext());

    llvm::SmallVector<llvm::Instruction*> ToRemove;

    for (auto User : MemoryArgument->users())
    {
        auto Instruction = llvm::dyn_cast<llvm::Instruction>(User);

        fassert(llvm::isa<llvm::GEPOperator>(Instruction));

        IR.SetInsertPoint(Instruction);
        Instruction->replaceAllUsesWith(IR.CreateIntToPtr(Instruction->getOperand(1), IR.getPtrTy()));
        ToRemove.push_back(Instruction);
    }

    for (auto Instruction : ToRemove)
    {
        Instruction->eraseFromParent();
    }
    return llvm::PreservedAnalyses::none();
}
