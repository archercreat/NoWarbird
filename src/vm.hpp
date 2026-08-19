#pragma once

#include "lifter.hpp"
#include "handler.hpp"

#include <array>

namespace vm
{
class VM
{
public:
    VM(const std::filesystem::path& Binary);

    llvm::Function* lift(key_t Key);

private:
    void descent(key_t Key);

    /// Disassemble and lift handler into IR and apply specific optimizations.
    ///
    std::shared_ptr<Handler> getHandler(key_t Key);

    llvm::Function* createStubFunction(const std::string& Name);

    llvm::Function* buildVirtualFunction(key_t Target = 0);

    std::unique_ptr<binary::MemoryManager> MemoryManager;
    std::unique_ptr<binary::Lifter> Lifter;

    llvm::LLVMContext Context;

    remill::Arch::ArchPtr Arch;
    /// This module holds remill semantics as well as raw lifted handlers.
    ///
    std::unique_ptr<llvm::Module> SemanticsModule;
    /// This module holds remill intrinsics as well as parsed handlers.
    ///
    std::unique_ptr<llvm::Module> HandlersModule;
    /// This module holds complete as well as partially lifted functions.
    ///
    std::unique_ptr<llvm::Module> OutputModule;
    /// Starting key value.
    ///
    key_t EntryKey;

    /// List of preloaded handler addresses.
    ///
    std::vector<uint64_t> Handlers;

    /// Current basic blocks in `main` function.
    ///
    std::unordered_map<key_t, std::shared_ptr<Handler>> LiftedHandlers;

    llvm::Function* HelperVirtualFunction;
    llvm::Function* HelperVirtualStub;
    llvm::Function* HelperRetainValue;
};
};
