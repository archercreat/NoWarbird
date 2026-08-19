#include "StackLifterPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <llvm/Analysis/ScalarEvolution.h>
#include <llvm/Analysis/ScalarEvolutionExpressions.h>

#include <llvm/Support/CommandLine.h>

#include <remill/BC/Util.h>
#include <remill/Arch/X86/Runtime/State.h>

static llvm::cl::opt<bool> StackLifterLoggingEnabled("log-stack", llvm::cl::init(false));

struct StackAccessInformation
{
    std::vector<llvm::CallInst*> ReadCalls;
    std::vector<llvm::CallInst*> WriteCalls;
    std::vector<llvm::StoreInst*> WriteStores;
    std::vector<llvm::LoadInst*> ReadLoads;
};

bool SCEVRSPLoad(const llvm::SCEVUnknown* SCEV)
{
    if (auto Load = llvm::dyn_cast<llvm::LoadInst>(SCEV->getValue()))
    {
        return GetRegisterByGetElementPtr(Load->getPointerOperand()) == X86RegisterNumber::RSP;
    }
    return false;
}

/// Analyze all memory reads and writes.
/// Get all stack offsets within the function.
/// Convert stack offsets into alloca instructions.
///
llvm::PreservedAnalyses StackLifterPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    llvm::IRBuilder<> IR(Function.getContext());

    std::unordered_map<uint64_t, StackAccessInformation> Stack;

    auto& SE = AM.getResult<llvm::ScalarEvolutionAnalysis>(Function);

    auto GetStackAccessOffset = [&](llvm::Value* Operand) -> std::optional<uint64_t>
    {
        auto SCEV = SE.getSCEV(Operand);
        // (16 + %0).
        //
        if (auto AddExpr = llvm::dyn_cast<llvm::SCEVAddExpr>(SCEV))
        {
            if (AddExpr->getNumOperands() == 2)
            {
                auto Op0 = AddExpr->getOperand(0);
                auto Op1 = AddExpr->getOperand(1);
                if (Op0->getSCEVType() == llvm::scConstant && Op1->getSCEVType() == llvm::scUnknown)
                {
                    auto Value    = llvm::dyn_cast<llvm::SCEVConstant>(Op0);
                    auto Variable = llvm::dyn_cast<llvm::SCEVUnknown>(Op1);
                    if (SCEVRSPLoad(Variable))
                        return Value->getValue()->getLimitedValue();
                }
            }
        }
        // %RSP
        else if (auto var = llvm::dyn_cast<llvm::SCEVUnknown>(SCEV))
        {
            if (SCEVRSPLoad(var))
                    return 0;
        }
        return {};
    };

    for (auto Read : GetMemoryReads(Function))
    {
        if (auto Offset = GetStackAccessOffset(Read->getArgOperand(1)))
        {
            Stack[Offset.value()].ReadCalls.push_back(Read);
        }
    }

    for (auto Write : GetMemoryWrites(Function))
    {
        if (auto Offset = GetStackAccessOffset(Write->getArgOperand(1)))
        {
            Stack[Offset.value()].WriteCalls.push_back(Write);
        }
    }

    for (auto& [Offset, Information] : Stack)
    {
        if (StackLifterLoggingEnabled)
        {
            logger::info("Found stack slot {}", static_cast<int64_t>(Offset));
        }
        // Create alloca instruction for each stack slot.
        //
        IR.SetInsertPoint(Function.getEntryBlock().getFirstInsertionPt());
        auto Alloca = IR.CreateAlloca(IR.getInt64Ty());
        // Now replace all calls to alloca loads and stores.
        //
        for (auto Call : Information.ReadCalls)
        {
            IR.SetInsertPoint(Call);
            Call->replaceAllUsesWith(IR.CreateLoad(Call->getCalledFunction()->getReturnType(), Alloca));
            Call->eraseFromParent();
        }
        for (auto Call : Information.WriteCalls)
        {
            IR.SetInsertPoint(Call);
            IR.CreateStore(Call->getArgOperand(2), Alloca);
            Call->replaceAllUsesWith(Call->getOperand(0));
            Call->eraseFromParent();
        }
    }

    return Stack.empty()
        ? llvm::PreservedAnalyses::all()
        : llvm::PreservedAnalyses::none();
}
