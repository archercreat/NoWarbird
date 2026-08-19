#pragma once

#include <llvm/IR/Module.h>

namespace vm
{
using key_t = uint64_t;

class Handler
{
public:
    Handler(llvm::Function* Function, std::vector<key_t> Successors);

    /// Lifted function of this handler.
    ///
    llvm::Function* Function;

    std::vector<key_t> GetSuccessors() const;
    void AddSuccessor(key_t Successor);

private:
    /// List of successors of this handler.
    ///
    std::vector<key_t> Successors;

    void RemoveDuplicates();
};
}
