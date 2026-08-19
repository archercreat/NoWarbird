#include "handler.hpp"

namespace vm
{
Handler::Handler(llvm::Function* Function, std::vector<key_t> Successors)
    : Function(Function), Successors(std::move(Successors))
{
    RemoveDuplicates();
}

void Handler::AddSuccessor(key_t Successor)
{
    Successors.push_back(Successor);
    RemoveDuplicates();
}

std::vector<key_t> Handler::GetSuccessors() const
{
    return Successors;
}

void Handler::RemoveDuplicates()
{
    std::sort(Successors.begin(), Successors.end());
    Successors.erase(std::unique(Successors.begin(), Successors.end()), Successors.end());
}
};
