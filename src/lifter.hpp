#pragma once
#include <remill/OS/OS.h>
#include <remill/Arch/Arch.h>
#include <remill/Arch/Name.h>
#include <remill/Arch/Instruction.h>
#include <remill/BC/IntrinsicTable.h>
#include <remill/BC/TraceLifter.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Object/ObjectFile.h>
#include <llvm/Support/MemoryBuffer.h>

#include <set>
#include <stack>
#include <vector>
#include <optional>
#include <functional>
#include <filesystem>

namespace binary
{
class MemoryManager
{
public:
    MemoryManager(const std::filesystem::path& Binary);

    std::optional<uint8_t> getByte(uint64_t Address) const;
    std::optional<std::string> getBytes(uint64_t Address, uint64_t Size) const;
    std::optional<uint64_t> getPointer(uint64_t Address) const;

    llvm::Triple::ArchType getArchType() const;
    llvm::Triple::ObjectFormatType getObjectFormatType() const;

    struct Section
    {
        llvm::StringRef Name;
        llvm::StringRef Contents;
        uint64_t        Size;
        uint64_t        Address;
    };
    std::optional<Section> getSection(uint64_t Address) const;

private:
    std::unique_ptr<llvm::object::ObjectFile> ObjectFile;
    std::unique_ptr<llvm::MemoryBuffer> MemoryBuffer;

    llvm::SmallVector<Section> Sections;
};

class Lifter
{
public:
    Lifter() = default;

    llvm::Function* lift(const remill::Arch* Arch, llvm::Module* SemanticsModule, const MemoryManager* MemoryManager, uint64_t Address);

    void operator()(const remill::Instruction::NormalInsn&);
    void operator()(const remill::Instruction::NoOp&);
    void operator()(const remill::Instruction::InvalidInsn&);
    void operator()(const remill::Instruction::ErrorInsn&);
    void operator()(const remill::Instruction::DirectJump&);
    void operator()(const remill::Instruction::IndirectJump&);
    void operator()(const remill::Instruction::IndirectFunctionCall&);
    void operator()(const remill::Instruction::DirectFunctionCall&);
    void operator()(const remill::Instruction::FunctionReturn&);
    void operator()(const remill::Instruction::AsyncHyperCall&);
    void operator()(const remill::Instruction::ConditionalInstruction&);

private:
    llvm::LLVMContext* CurrentContext;
    const remill::Arch* CurrentArch;
    llvm::Module* CurrentModule;

    llvm::BasicBlock* getOrCreateBlock(uint64_t to, uint64_t from);
    llvm::BasicBlock* getOrCreateNextBlock();
    llvm::BasicBlock* getOrCreateTakenBlock();
    llvm::BasicBlock* getOrCreateNotTakenBlock();

    using edge_t = std::pair<uint64_t, uint64_t>;

    llvm::Function* CurrentFunction;
    llvm::BasicBlock* CurrentBlock;
    remill::Instruction CurrentInstruction;
    std::vector<uint64_t> CurrentStack;

    /// Current list of blocks for exploration.
    ///
    std::set<edge_t> Worklist;

    /// Currnet control-flow edges between instructions.
    ///
    std::map<edge_t, llvm::BasicBlock*> Edges;
};
};
