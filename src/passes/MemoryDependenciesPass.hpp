#pragma once

#include <llvm/IR/PassManager.h>

class MemoryDependenciesPass : public llvm::PassInfoMixin<MemoryDependenciesPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
