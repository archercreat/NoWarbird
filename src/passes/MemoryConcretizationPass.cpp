#include "MemoryConcretizationPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/PatternMatch.h>
#include <llvm/Transforms/Utils/Cloning.h>
#include <remill/BC/Util.h>
#include <remill/Arch/X86/Runtime/State.h>

static llvm::cl::opt<bool> MemoryConcretizationLoggingEnabled(
    "log-memory-reads",
    llvm::cl::init(false)
);

std::set<llvm::StringRef> ConstantSections =
{
    ".rdata",
    ".pdata",
    ".idata",
    ".xdata",
    ".edata",
    "PAGECONS",
    "PAGEDATA",
    "GFIDS"
};

llvm::PreservedAnalyses MemoryConcretizationPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    llvm::IRBuilder<> IR(Function.getContext());

    std::vector<std::pair<llvm::Instruction*, llvm::ConstantInt*>> MemoryLoads;

    auto MemoryArgument = GetFunctionArgument(&Function, MainFunctionArgument::Memory);

    llvm::Value* Memory{};
    uint64_t Address{};

    auto Pattern = llvm::PatternMatch::m_Load(
        llvm::PatternMatch::m_GEP(
            llvm::PatternMatch::m_Value(Memory),
            llvm::PatternMatch::m_ConstantInt(Address)
        )
    );

    for (auto& Instruction : llvm::instructions(Function))
    {
        // Memory concretization pass run at the late stages of devirtualization
        //
        if (llvm::PatternMatch::match(&Instruction, Pattern) && Memory == MemoryArgument)
        {
            if (auto Section = MemoryManager->getSection(Address))
            {
                if (ConstantSections.contains(Section->Name))
                {
                    if (MemoryConcretizationLoggingEnabled)
                    {
                        logger::info("concrete read from 0x{:x}", Address);
                    }
                    // Found load from constant section. Replace with concrete value.
                    //
                    auto Value = MemoryManager->getPointer(Address);
                    auto Bits  = llvm::dyn_cast<llvm::IntegerType>(Instruction.getAccessType())->getBitWidth();
                    MemoryLoads.emplace_back(&Instruction, IR.getIntN(Bits, Value.value()));
                }
            }
            else
            {
                if (MemoryConcretizationLoggingEnabled)
                {
                    logger::warn("No section found for address 0x{:x}", Address);
                }
            }
        }
    }

    for (auto [Instruction, Constant] : MemoryLoads)
    {
        Instruction->replaceAllUsesWith(Constant);
        Instruction->eraseFromParent();
    }

    return MemoryLoads.empty()
        ? llvm::PreservedAnalyses::all()
        : llvm::PreservedAnalyses::none();
}
