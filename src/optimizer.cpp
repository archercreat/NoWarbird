#include "optimizer.hpp"
#include "lifter.hpp"
#include "logger.hpp"

#include "passes/InlinerPass.hpp"
#include "passes/StackLifterPass.hpp"
#include "passes/StateRemoverPass.hpp"
#include "passes/UndefRemoverPass.hpp"
#include "passes/MemoryRemoverPass.hpp"
#include "passes/VirtualStackLifterPass.hpp"
#include "passes/MemoryDependenciesPass.hpp"
#include "passes/InstCombineSpecificPass.hpp"
#include "passes/MemoryConcretizationPass.hpp"

#include <llvm/IR/InstIterator.h>
#include <llvm/Analysis/ScopedNoAliasAA.h>
#include <llvm/Analysis/BasicAliasAnalysis.h>
#include <llvm/Analysis/TypeBasedAliasAnalysis.h>
#include <llvm/Analysis/ScalarEvolutionAliasAnalysis.h>

static constexpr auto OptimizationRetryCount = 5;

Optimizer::Optimizer(llvm::Function* Function)
    : Function(Function)
{
}

Optimizer&& Optimizer::exhaustOptimizations(bool on)
{
    this->ExhaustOptimizations = on;
    return std::move(*this);
}

Optimizer&& Optimizer::inlineFunctionCalls(bool on)
{
    this->InlineFunctionCalls = on;
    return std::move(*this);
}

Optimizer&& Optimizer::inlineMemoryIntrinsics(bool on)
{
    this->InlineMemoryIntrinsics = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableMemoryDependencyPass(bool on)
{
    this->EnableMemoryDependencyPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::stripSymbolNames(bool on)
{
    this->StripSymbolNames = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableStackLifterPass(bool on)
{
    this->EnableStackLifterPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableStateRemoverPass(bool on, StateRemoveStrategy Strategy)
{
    this->Strategy = Strategy;
    this->EnableStateRemoverPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableUndefRemoverPass(bool on)
{
    this->EnableUndefRemoverPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableMemoryConcretizationPass(bool on, binary::MemoryManager* MemoryManager)
{
    this->EnableMemoryConcretizationPass = on;
    this->MemoryManager = MemoryManager;
    return std::move(*this);
}

Optimizer&& Optimizer::enableVirtualStackLifterPass(bool on)
{
    this->EnableVirtualStackLifterPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableInstCombineSpecificPass(bool on)
{
    this->EnableInstCombineSpecificPass = on;
    return std::move(*this);
}

Optimizer&& Optimizer::enableMemoryRemoverPass(bool on)
{
    this->EnableMemoryRemoverPass = on;
    return std::move(*this);
}

void Optimizer::run() const
{
    llvm::PassBuilder             PB;
    llvm::LoopAnalysisManager     LAM;
    llvm::CGSCCAnalysisManager    CAM;
    llvm::ModuleAnalysisManager   MAM;
    llvm::FunctionAnalysisManager FAM;

    auto FPM = PB.buildFunctionSimplificationPipeline(
        llvm::OptimizationLevel::O3,
        llvm::ThinOrFullLTOPhase::ThinLTOPreLink);

    PB.registerLoopAnalyses(LAM);
    PB.registerCGSCCAnalyses(CAM);
    PB.registerModuleAnalyses(MAM);
    PB.registerFunctionAnalyses(FAM);
    PB.crossRegisterProxies(LAM, FAM, CAM, MAM);

    // Make inliner pass run before any other passes.
    // That way, for some reason, MemoryConcretizationPass is able to find more
    // concrete memory loads.
    //
    if (InlineFunctionCalls)
    {
        FPM.addPass(InlinerPass(InlineMemoryIntrinsics));
        FPM.run(*Function, FAM);
        // Remove inliner pass from the pipeline.
        //
        FPM = PB.buildFunctionSimplificationPipeline(
            llvm::OptimizationLevel::O3,
            llvm::ThinOrFullLTOPhase::ThinLTOPreLink);
    }

    if (EnableStackLifterPass)
    {
        FPM.addPass(StackLifterPass());
    }
    if (EnableStateRemoverPass)
    {
        FPM.addPass(StateRemoverPass(Strategy));
    }
    if (EnableUndefRemoverPass)
    {
        FPM.addPass(UndefRemoverPass());
    }
    if (EnableMemoryDependencyPass)
    {
        FPM.addPass(MemoryDependenciesPass());
    }
    if (EnableMemoryConcretizationPass)
    {
        FPM.addPass(MemoryConcretizationPass(MemoryManager));
    }
    if (EnableVirtualStackLifterPass)
    {
        FPM.addPass(VirtualStackLifterPass());
    }
    if (EnableInstCombineSpecificPass)
    {
        FPM.addPass(InstCombineSpecificPass());
    }
    if (EnableMemoryRemoverPass)
    {
        FPM.addPass(MemoryRemoverPass());
    }

    if (ExhaustOptimizations)
    {
        uint64_t InstructionCount = Function->getInstructionCount();
        uint64_t Tries{};
        while (true)
        {
            FPM.run(*Function, FAM);
            if (InstructionCount > Function->getInstructionCount())
            {
                InstructionCount = Function->getInstructionCount();
                Tries = 0;
            }
            else if (Tries++ > OptimizationRetryCount)
            {
                break;
            }
        }
    }
    else
    {
        FPM.run(*Function, FAM);
    }

    if (StripSymbolNames)
    {
        for (auto& Instruction : llvm::instructions(Function))
        {
            Instruction.setName("");
        }
    }
}
