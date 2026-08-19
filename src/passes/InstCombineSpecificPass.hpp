#pragma once

#include <llvm/IR/PassManager.h>

class InstCombineSpecificPass : public llvm::PassInfoMixin<InstCombineSpecificPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
