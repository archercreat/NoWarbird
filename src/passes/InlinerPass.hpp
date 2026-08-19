#pragma once

#include <llvm/IR/PassManager.h>

class InlinerPass : public llvm::PassInfoMixin<InlinerPass>
{
public:
    explicit InlinerPass(bool InlineIntrinsicFunctions);
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);
private:
    bool InlineIntrinsicFunctions;
};
