#pragma once

#include <llvm/IR/PassManager.h>

class VirtualStackLifterPass : public llvm::PassInfoMixin<VirtualStackLifterPass>
{
public:
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
};
