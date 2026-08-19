#pragma once

#include <llvm/IR/PassManager.h>

enum class StateRemoveStrategy
{
    CreateStore,
    RemoveStore
};

class StateRemoverPass : public llvm::PassInfoMixin<StateRemoverPass>
{
public:
    StateRemoverPass(StateRemoveStrategy Strategy);
    llvm::PreservedAnalyses run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM);

private:
    StateRemoveStrategy Strategy;
};
