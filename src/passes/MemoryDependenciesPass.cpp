#include "passes/MemoryDependenciesPass.hpp"
#include "logger.hpp"
#include <llvm/Analysis/AliasAnalysis.h>
#include <llvm/Analysis/PostDominators.h>
#include <llvm/Analysis/ScalarEvolution.h>
#include <llvm/Analysis/MemoryDependenceAnalysis.h>
#include <llvm/Analysis/ScalarEvolutionAliasAnalysis.h>
#include <llvm/IR/InstIterator.h>

/// This pass is useful to debug aliasing errors.
///
llvm::PreservedAnalyses MemoryDependenciesPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    auto& MDA = AM.getResult<llvm::MemoryDependenceAnalysis>(Function);
    for (auto& Instruction : llvm::instructions(Function))
    {
        if (llvm::isa<llvm::LoadInst>(Instruction) || llvm::isa<llvm::StoreInst>(Instruction))
        {
            auto Dependency = MDA.getDependency(&Instruction).getInst();
            if (Dependency != nullptr)
            {
                logger::debug("memory dependence:");
                Instruction.dump();
                Dependency->dump();
            }
        }
    }
    return llvm::PreservedAnalyses::all();
}
