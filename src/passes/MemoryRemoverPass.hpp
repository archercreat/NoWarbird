#pragma once

#include <llvm/IR/PassManager.h>

class MemoryRemoverPass : public llvm::PassInfoMixin<MemoryRemoverPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
