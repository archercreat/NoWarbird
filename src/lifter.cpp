#include "utils.hpp"
#include "lifter.hpp"
#include "logger.hpp"
#include "optimizer.hpp"

#include <llvm/Linker/Linker.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <llvm/ADT/Statistic.h>

#include <llvm/Support/Error.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/CommandLine.h>

#include <remill/BC/Util.h>
#include <remill/BC/Optimizer.h>
#include <remill/Arch/Instruction.h>

/// Some statistics.
///
#define DEBUG_TYPE "warbird-lifter"

ALWAYS_ENABLED_STATISTIC(LiftedFunctions, "Number of raw functions lifted");
ALWAYS_ENABLED_STATISTIC(LiftedInstructions, "Number of raw machine instructions lifted");

namespace binary
{
MemoryManager::MemoryManager(const std::filesystem::path& Binary)
{
    auto ObjectOrError = llvm::object::ObjectFile::createObjectFile(Binary.string());
    if (!ObjectOrError)
    {
        logger::error("Failed to create object file from {}", Binary.string());
    }

    std::tie(ObjectFile, MemoryBuffer) = ObjectOrError->takeBinary();

    for (const auto& Section : ObjectFile->sections())
    {
        auto SectionName           = Section.getName();
        auto SectionVirtualAddress = Section.getAddress();
        auto SectionSize           = Section.getSize();
        auto SectionContents       = Section.getContents();

        if (!SectionContents)
        {
            logger::error("Section at 0x{:x} has no data", SectionVirtualAddress);
        }
        if (!SectionName)
        {
            logger::error("Section at 0x{:x} has no name", SectionVirtualAddress);
        }
        // Section.getSize() returns the number of valid bytes in the section.
        // Not to be confused with sections raw size which is aligned.
        // This is why we align this number by page size to get sections virtual size.
        //
        constexpr auto Alignment = 4096;
        if ((SectionSize & (Alignment - 1)) != 0)
        {
            SectionSize = (SectionSize + Alignment) & ~(Alignment - 1);
        }

        Sections.emplace_back(MemoryManager::Section{
            .Name     = SectionName.get(),
            .Contents = SectionContents.get(),
            .Size     = SectionSize,
            .Address  = SectionVirtualAddress
        });

        logger::info("{:<10} 0x{:08x} 0x{:06x}", SectionName->str(), SectionVirtualAddress, SectionSize);
    }
}

std::optional<uint8_t> MemoryManager::getByte(uint64_t Address) const
{
    if (auto Section = getSection(Address))
    {
            auto Offset   = Address - Section->Address;
            auto Contents = Section->Contents;
            if (Offset >= Contents.size())
            {
                return '\x00';
            }
            return Contents[Offset];
    }
    return {};
}

std::optional<std::string> MemoryManager::getBytes(uint64_t Address, uint64_t Size) const
{
    if (auto Section = getSection(Address))
    {
        auto Offset   = Address - Section->Address;
        auto Contents = Section->Contents;

        if (Section->Size >= Offset + Size)
        {
            return Contents.substr(Offset, Size).str();
        }
        else
        {
            // We are at the edge of the section. Get the value and pad with zeroes.
            //
            auto Data = Contents.substr(Offset).str();
            for (unsigned i = Data.size(); i < Size; i++)
                Data += "\x00";
            return Data;
        }
    }
    return {};
}

std::optional<uint64_t> MemoryManager::getPointer(uint64_t Address) const
{
    if (auto Section = getSection(Address))
    {
        auto Offset   = Address - Section->Address;
        auto Contents = Section->Contents;
        if (Offset + sizeof(uint64_t) >= Section->Size)
        {
            logger::warn("Could not read value on sections boundary 0x{:x}", Address);
            return {};
        }
        if (Offset + sizeof(uint64_t) < Contents.size())
        {
            return *reinterpret_cast<const uint64_t*>(Contents.substr(Offset, 8).data());
        }
        // We are at the edge of the section. Get the value and pad with zeroes.
        //
        auto Data = Contents.substr(Offset).str();
        for (unsigned i = Data.size(); i < sizeof(uint64_t); i++)
        {
            Data += "\x00";
        }
        return *reinterpret_cast<const uint64_t*>(Data.data());
    }
    return {};
}

std::optional<MemoryManager::Section> MemoryManager::getSection(uint64_t Address) const
{
    for (const auto& Section : Sections)
    {
        if (Address >= Section.Address && Address < Section.Address + Section.Size)
        {
            return Section;
        }
    }
    return {};
}

llvm::Triple::ArchType MemoryManager::getArchType() const
{
    return ObjectFile->getArch();
}

llvm::Triple::ObjectFormatType MemoryManager::getObjectFormatType() const
{
    return ObjectFile->getTripleObjectFormat();
}

llvm::Function* Lifter::lift(const remill::Arch* Arch, llvm::Module* SemanticsModule, const MemoryManager* MemoryManager, uint64_t Address)
{
    LiftedFunctions++;

    CurrentContext = &SemanticsModule->getContext();
    CurrentArch = Arch;
    CurrentModule = SemanticsModule;

    const auto FunctionName = fmt::format("sub_0x{:x}", Address);
    CurrentFunction = CurrentModule->getFunction(FunctionName);
    if (CurrentFunction != nullptr)
    {
        return CurrentFunction;
    }

    CurrentFunction = Arch->DefineLiftedFunction(fmt::format("sub_0x{:x}.{}", Address, LiftedFunctions), CurrentModule);
    CurrentFunction->addFnAttr(llvm::Attribute::AlwaysInline);
    CurrentFunction->addFnAttr(llvm::Attribute::InlineHint);
    // Clear cache from previous runs.
    //
    Edges.clear();
    Worklist.clear();
    CurrentStack.clear();
    // Branch to the first basic block.
    //
    llvm::BranchInst::Create(getOrCreateBlock(Address, 0), &CurrentFunction->getEntryBlock());

    Worklist.emplace(Address, 0);

    while (!Worklist.empty())
    {
        auto [InstructionAddress, FromAddress] = *Worklist.begin();
        Worklist.erase(Worklist.begin());

        CurrentBlock = Edges[{InstructionAddress, FromAddress}];

        // Skip already explored.
        //
        if (!CurrentBlock->empty())
            continue;

        CurrentInstruction.Reset();
        // Read raw bytes.
        //
        if (auto Raw = MemoryManager->getBytes(InstructionAddress, 16); Raw.has_value())
        {
            if (!Arch->DecodeInstruction(InstructionAddress, Raw.value(), CurrentInstruction, Arch->CreateInitialContext()))
            {
                logger::error("Failed to decode instruction at 0x{:x}", InstructionAddress);
            }
        }
        else
        {
            logger::warn("Failed to read 0x{:x}", InstructionAddress);
            remill::AddTerminatingTailCall(CurrentBlock, Arch->GetInstrinsicTable()->error, *Arch->GetInstrinsicTable());
            continue;
        }
        // We don't lift function calls.
        //
        if (!CurrentInstruction.IsFunctionCall() && !CurrentInstruction.IsFunctionReturn())
        {
            if (CurrentInstruction.GetLifter()->LiftIntoBlock(CurrentInstruction, CurrentBlock) != remill::kLiftedInstruction)
            {
                logger::warn("Failed to lift instruction at 0x{:x}", InstructionAddress);
                AddTerminatingTailCall(CurrentBlock, Arch->GetInstrinsicTable()->error, *Arch->GetInstrinsicTable());
                continue;
            }
        }
        LiftedInstructions++;
        // Process control flow.
        //
        std::visit(*this, CurrentInstruction.flows);
    }
    // Terminate every block.
    //
    for (auto& Block : *CurrentFunction)
    {
        if (!Block.getTerminator())
        {
            remill::AddTerminatingTailCall(&Block, Arch->GetInstrinsicTable()->missing_block, *Arch->GetInstrinsicTable());
        }
    }
    auto ProgramCounter = remill::NthArgument(CurrentFunction, remill::kPCArgNum);
    ProgramCounter->replaceAllUsesWith(
        llvm::ConstantInt::get(ProgramCounter->getType(), Address));
    remill::OptimizeBareModule(CurrentModule, {});
    return CurrentFunction;
}

llvm::BasicBlock* Lifter::getOrCreateBlock(uint64_t To, uint64_t From)
{
    auto& Block = Edges[{ To, From }];
    if (Block)
    {
        return Block;
    }
    Block = llvm::BasicBlock::Create(*CurrentContext, fmt::format("inst_0x{:x}", To), CurrentFunction);

    Worklist.emplace(To, From);
    return Block;
}

llvm::BasicBlock* Lifter::getOrCreateNextBlock()
{
    return getOrCreateBlock(CurrentInstruction.next_pc, CurrentInstruction.pc);
}

llvm::BasicBlock* Lifter::getOrCreateTakenBlock()
{
    return getOrCreateBlock(CurrentInstruction.branch_taken_pc, CurrentInstruction.pc);
}

llvm::BasicBlock* Lifter::getOrCreateNotTakenBlock()
{
    return getOrCreateBlock(CurrentInstruction.branch_not_taken_pc, CurrentInstruction.pc);
}

void Lifter::operator()(const remill::Instruction::NormalInsn&)
{
    llvm::BranchInst::Create(getOrCreateNextBlock(), CurrentBlock);
}

void Lifter::operator()(const remill::Instruction::NoOp&)
{
    llvm::BranchInst::Create(getOrCreateNextBlock(), CurrentBlock);
}

void Lifter::operator()(const remill::Instruction::InvalidInsn&)
{
    remill::AddTerminatingTailCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->error, *CurrentArch->GetInstrinsicTable());
}

void Lifter::operator()(const remill::Instruction::ErrorInsn&)
{
    remill::AddTerminatingTailCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->error, *CurrentArch->GetInstrinsicTable());
}

void Lifter::operator()(const remill::Instruction::DirectJump&)
{
    llvm::BranchInst::Create(getOrCreateTakenBlock(), CurrentBlock);
}

void Lifter::operator()(const remill::Instruction::IndirectJump&)
{
    remill::AddTerminatingTailCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->jump, *CurrentArch->GetInstrinsicTable());
}

void Lifter::operator()(const remill::Instruction::IndirectFunctionCall&)
{
    remill::AddTerminatingTailCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->function_return, *CurrentArch->GetInstrinsicTable());
}

void Lifter::operator()(const remill::Instruction::DirectFunctionCall&)
{
    auto TargetAddress = CurrentInstruction.branch_taken_pc;
    if (TargetAddress == 0x1C0029DC0) // memset
    {
        auto Dst = LoadRegister(X86RegisterNumber::RCX, CurrentBlock);
        auto Val = LoadRegister(X86RegisterNumber::RDX, CurrentBlock);
        auto Len = LoadRegister(X86RegisterNumber::R8, CurrentBlock);

        llvm::IRBuilder<> IR(CurrentBlock);

        Val = IR.CreateTrunc(Val, IR.getInt8Ty());

        auto Memory = remill::NthArgument(CurrentFunction, remill::kMemoryPointerArgNum);

        IR.CreateMemSetInline(
            IR.CreateInBoundsGEP(Memory->getType(), Memory, {Dst}),
            llvm::MaybeAlign(8),
            Val,
            Len
        );
        llvm::BranchInst::Create(getOrCreateNotTakenBlock(), CurrentBlock);
    }
    else if (TargetAddress == 0x1C0007340) // FreePool
    {
        llvm::IRBuilder<> IR(CurrentBlock);
        auto FunctionName = fmt::format("ext_0x{:x}", TargetAddress);
        auto FunctionType = llvm::FunctionType::get(IR.getVoidTy(), { IR.getInt64Ty() }, false);
        auto ExternalFunction = llvm::Function::Create(FunctionType, llvm::GlobalValue::LinkageTypes::ExternalLinkage, FunctionName, CurrentModule);
        ExternalFunction->setMemoryEffects(llvm::MemoryEffects::none());
        IR.CreateCall(ExternalFunction, {
            LoadRegister(X86RegisterNumber::RCX, CurrentBlock)
        });
        llvm::BranchInst::Create(getOrCreateNotTakenBlock(), CurrentBlock);
    }
    else if (TargetAddress == 0x1C0007314) // AllocatePool
    {
        llvm::IRBuilder<> IR(CurrentBlock);
        auto FunctionName = fmt::format("ext_0x{:x}", TargetAddress);
        auto FunctionType = llvm::FunctionType::get(IR.getInt64Ty(), { IR.getInt64Ty() }, false);
        auto ExternalFunction = llvm::Function::Create(FunctionType, llvm::GlobalValue::LinkageTypes::ExternalLinkage, FunctionName, CurrentModule);
        ExternalFunction->setMemoryEffects(llvm::MemoryEffects::none());
        auto Result = IR.CreateCall(ExternalFunction, {
            LoadRegister(X86RegisterNumber::RCX, CurrentBlock)
        });
        StoreRegister(X86RegisterNumber::RAX, Result, CurrentBlock);
        llvm::BranchInst::Create(getOrCreateNotTakenBlock(), CurrentBlock);
    }
    else if (TargetAddress == 0x1C00AD150 || TargetAddress == 0x1C00B2904)
    {
        CurrentStack.push_back(CurrentInstruction.branch_not_taken_pc);
        llvm::BranchInst::Create(getOrCreateTakenBlock(), CurrentBlock);
    }
    else
    {
        logger::error("Unsupported call");
    }
}

void Lifter::operator()(const remill::Instruction::FunctionReturn&)
{
    if (CurrentStack.empty())
    {
        remill::AddTerminatingTailCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->function_return, *CurrentArch->GetInstrinsicTable());
    }
    else
    {
        auto ReturnAddress = CurrentStack.back(); CurrentStack.pop_back();
        llvm::BranchInst::Create(getOrCreateBlock(ReturnAddress, CurrentInstruction.pc), CurrentBlock);
    }
}

void Lifter::operator()(const remill::Instruction::AsyncHyperCall&)
{
    remill::AddCall(CurrentBlock, CurrentArch->GetInstrinsicTable()->async_hyper_call, *CurrentArch->GetInstrinsicTable());
}

void Lifter::operator()(const remill::Instruction::ConditionalInstruction&)
{
    auto Taken    = getOrCreateTakenBlock();
    auto NotTaken = getOrCreateNotTakenBlock();
    llvm::BranchInst::Create(Taken, NotTaken, remill::LoadBranchTaken(CurrentBlock), CurrentBlock);
}
};
