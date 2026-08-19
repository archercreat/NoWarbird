#pragma once

#include <llvm/IR/PassManager.h>

class UndefRemoverPass : public llvm::PassInfoMixin<UndefRemoverPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
