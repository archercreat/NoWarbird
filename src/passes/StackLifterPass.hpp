#pragma once

#include <llvm/IR/PassManager.h>

class StackLifterPass : public llvm::PassInfoMixin<StackLifterPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
