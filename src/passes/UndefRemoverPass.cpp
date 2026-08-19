#include "UndefRemoverPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/InstIterator.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <remill/BC/Util.h>
#include <remill/Arch/X86/Runtime/State.h>

llvm::PreservedAnalyses UndefRemoverPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    bool Modified{};
    auto Undef = GetGlobalUndefVariable(Function.getParent());
    for (auto User : Undef->users())
    {
        if (auto Load = llvm::dyn_cast<llvm::LoadInst>(User))
        {
            if (auto parent = Load->getParent()->getParent())
            {
                if (parent == &Function)
                {
                    Load->replaceAllUsesWith(llvm::UndefValue::get(Load->getType()));
                    Modified = true;
                }
            }
        }
    }
    return Modified
        ? llvm::PreservedAnalyses::none()
        : llvm::PreservedAnalyses::all();
}
