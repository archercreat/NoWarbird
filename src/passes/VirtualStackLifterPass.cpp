#include "VirtualStackLifterPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IR/PatternMatch.h>

llvm::PreservedAnalyses VirtualStackLifterPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    auto MemoryArgument       = GetFunctionArgument(&Function, MainFunctionArgument::Memory);
    auto StackPointerArgument = GetFunctionArgument(&Function, MainFunctionArgument::VSP);

    llvm::IRBuilder<> IR(Function.getContext());
    auto Uint8Type = IR.getInt8Ty();

    llvm::Value* Alloca = nullptr;
    auto StackAccessPattern = llvm::PatternMatch::m_PtrToInt(
        llvm::PatternMatch::m_Load(llvm::PatternMatch::m_Value(Alloca))
    );

    llvm::ConstantInt* StackConstant = nullptr;
    auto StackDisplacementPattern = llvm::PatternMatch::m_Add(
        StackAccessPattern, llvm::PatternMatch::m_ConstantInt(StackConstant));

    llvm::Value* Memory = nullptr;
    auto MemoryPattern = llvm::PatternMatch::m_GEP(
        llvm::PatternMatch::m_Value(Memory),
        StackAccessPattern
    );

    llvm::Value* MemoryDisplacement = nullptr;
    auto MemoryDisplacementPattern = llvm::PatternMatch::m_GEP(
        llvm::PatternMatch::m_GEP(llvm::PatternMatch::m_Value(Memory), llvm::PatternMatch::m_Value(MemoryDisplacement)),
        StackAccessPattern
    );

    auto MemoryStackDisplacementPattern = llvm::PatternMatch::m_GEP(
        llvm::PatternMatch::m_Value(Memory),
        StackDisplacementPattern
    );

    auto MemoryDisplacementStackDisplacementPattern = llvm::PatternMatch::m_GEP(
        llvm::PatternMatch::m_GEP(llvm::PatternMatch::m_Value(Memory), llvm::PatternMatch::m_Value(MemoryDisplacement)),
        StackDisplacementPattern
    );

    // The function is not fully optimized yet.
    //
    if (StackPointerArgument->getNumUses() > 1)
    {
        return llvm::PreservedAnalyses::all();
    }

    // One user is a store instruction to alloca instruction.
    //
    fassert(StackPointerArgument->hasOneUser());
    auto LocalPointerStorage = llvm::dyn_cast<llvm::StoreInst>(*StackPointerArgument->users().begin())->getPointerOperand();

    llvm::SmallVector<llvm::Instruction*> ToRemove;

    llvm::Instruction* PtrToIntInstruction = nullptr;

    for (auto& Instruction : llvm::instructions(Function))
    {
        if (llvm::PatternMatch::match(&Instruction, StackAccessPattern))
        {
            fassert(Alloca == LocalPointerStorage);
            PtrToIntInstruction = &Instruction;
            break;
        }
    }

    fassert(PtrToIntInstruction != nullptr);

    for (auto& Instruction : llvm::instructions(Function))
    {
        if (llvm::PatternMatch::match(&Instruction, MemoryDisplacementStackDisplacementPattern))
        {
            fassert(Alloca == LocalPointerStorage);
            fassert(Memory == MemoryArgument);

            IR.SetInsertPoint(&Instruction);

            auto NewInstruction = IR.CreateGEP(Uint8Type, StackPointerArgument, { IR.CreateAdd(StackConstant, MemoryDisplacement) });
            logger::info("Replacing {}", ValueToString(&Instruction));
            logger::info("With      {}", ValueToString(NewInstruction));
            Instruction.replaceAllUsesWith(NewInstruction);

            ToRemove.push_back(&Instruction);
        }
        else if (llvm::PatternMatch::match(&Instruction, MemoryStackDisplacementPattern))
        {
            Instruction.dump();
            fassert(Alloca == LocalPointerStorage);
            fassert(Memory == MemoryArgument);

            IR.SetInsertPoint(&Instruction);

            auto NewInstruction = IR.CreateGEP(Uint8Type, StackPointerArgument, { StackConstant });
            logger::info("Replacing {}", ValueToString(&Instruction));
            logger::info("With      {}", ValueToString(NewInstruction));
            Instruction.replaceAllUsesWith(NewInstruction);

            ToRemove.push_back(&Instruction);
        }
        if (llvm::PatternMatch::match(&Instruction, MemoryDisplacementPattern))
        {
            fassert(Alloca == LocalPointerStorage);
            fassert(Memory == MemoryArgument);

            IR.SetInsertPoint(&Instruction);

            auto NewInstruction = IR.CreateGEP(Uint8Type, StackPointerArgument, { MemoryDisplacement });
            logger::info("Replacing {}", ValueToString(&Instruction));
            logger::info("With      {}", ValueToString(NewInstruction));
            Instruction.replaceAllUsesWith(NewInstruction);

            ToRemove.push_back(&Instruction);
        }
        else if (llvm::PatternMatch::match(&Instruction, MemoryPattern))
        {
            fassert(Alloca == LocalPointerStorage);
            fassert(Memory == MemoryArgument);

            IR.SetInsertPoint(&Instruction);

            auto NewInstruction = IR.CreateGEP(Uint8Type, StackPointerArgument, { IR.getInt64(0) });
            logger::info("Replacing {}", ValueToString(&Instruction));
            logger::info("With      {}", ValueToString(NewInstruction));
            Instruction.replaceAllUsesWith(NewInstruction);

            ToRemove.push_back(&Instruction);
        }
    }

    for (auto Instruction : ToRemove)
        Instruction->eraseFromParent();

    // Either PtrToInt instruction has no users or its users have no users and DCE
    // will remove them.
    //
    for (auto User : PtrToIntInstruction->users())
    {
        User->dump();
    }

    return llvm::PreservedAnalyses::none();
}
