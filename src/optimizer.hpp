#pragma once
#include "passes/StateRemoverPass.hpp"

#include <remill/Arch/Arch.h>
#include <llvm/Passes/PassBuilder.h>

namespace llvm
{
class Function;
class Module;
};

namespace binary
{
class MemoryManager;
};

class Optimizer
{
public:
    explicit Optimizer(llvm::Function* Function);

    Optimizer&& exhaustOptimizations(bool on);
    Optimizer&& inlineFunctionCalls(bool on);
    Optimizer&& inlineMemoryIntrinsics(bool on);
    Optimizer&& enableMemoryDependencyPass(bool on);
    Optimizer&& stripSymbolNames(bool on);
    Optimizer&& enableStackLifterPass(bool on);
    Optimizer&& enableStateRemoverPass(bool on, StateRemoveStrategy Strategy);
    Optimizer&& enableUndefRemoverPass(bool on);
    Optimizer&& enableMemoryConcretizationPass(bool on, binary::MemoryManager* MemoryManager);
    Optimizer&& enableVirtualStackLifterPass(bool on);
    Optimizer&& enableInstCombineSpecificPass(bool on);
    Optimizer&& enableMemoryRemoverPass(bool on);

    void run() const;

private:
    llvm::Function* Function;
    binary::MemoryManager* MemoryManager{};
    bool StripSymbolNames{};
    bool ExhaustOptimizations{};
    bool InlineFunctionCalls{};
    bool InlineMemoryIntrinsics{};
    bool EnableMemoryDependencyPass{};
    bool EnableStackLifterPass{};
    StateRemoveStrategy Strategy;
    bool EnableStateRemoverPass{};
    bool EnableUndefRemoverPass{};
    bool EnableMemoryConcretizationPass{};
    bool EnableVirtualStackLifterPass{};
    bool EnableInstCombineSpecificPass{};
    bool EnableMemoryRemoverPass{};
};
