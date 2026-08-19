#pragma once
#include "lifter.hpp"

#include <llvm/IR/PassManager.h>

/// Look for reads from constant sections and replace with concrete values.
///
class MemoryConcretizationPass : public llvm::PassInfoMixin<MemoryConcretizationPass>
{
public:
    MemoryConcretizationPass(binary::MemoryManager* MemoryManager) : MemoryManager(MemoryManager) {};
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);

private:
    binary::MemoryManager* MemoryManager;
};
