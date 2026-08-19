#include "StateRemoverPass.hpp"
#include "utils.hpp"
#include "logger.hpp"

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/PatternMatch.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <remill/BC/Util.h>
#include <remill/Arch/X86/Runtime/State.h>

StateRemoverPass::StateRemoverPass(StateRemoveStrategy Strategy)
    : Strategy(Strategy)
{
}

llvm::PreservedAnalyses StateRemoverPass::run(llvm::Function& Function, llvm::FunctionAnalysisManager& AM)
{
    auto Undef = GetGlobalUndefVariable(Function.getParent());
    auto StateArgument = remill::NthArgument(&Function, remill::kStatePointerArgNum);

    if (Strategy == StateRemoveStrategy::CreateStore)
    {
        for (auto& Block : Function)
        {
            if (auto Ret = llvm::dyn_cast<llvm::ReturnInst>(Block.getTerminator()))
            {
                llvm::IRBuilder<> IR(Ret);
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::CF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::PF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::AF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::ZF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::SF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::DF) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt8Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::OF) }));

                // IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RAX) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RBX) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RCX) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RDX) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RSI) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RDI) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RSP) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RBP) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R8)  }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R9)  }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R10) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R11) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R12) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R13) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R14) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::R15) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RIP) }));
                IR.CreateStore(IR.CreateLoad(IR.getInt64Ty(), Undef), IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(X86RegisterNumber::RFLAGS) }));
            }
        }
    }
    else if (Strategy == StateRemoveStrategy::RemoveStore)
    {
        llvm::SmallVector<llvm::StoreInst*> ToRemove;

        auto ValidateOperand = [](llvm::Value* Operand)
        {
            auto Register = GetRegisterByGetElementPtr(Operand);
            return Register != X86RegisterNumber::INVALID && Register != X86RegisterNumber::RAX;
        };

        for (auto& Instruction : llvm::instructions(Function))
        {
            if (auto Store = llvm::dyn_cast<llvm::StoreInst>(&Instruction))
            {
                if (ValidateOperand(Store->getPointerOperand()))
                {
                    ToRemove.push_back(Store);
                }
                else if (auto PHI = llvm::dyn_cast<llvm::PHINode>(Store->getPointerOperand()))
                {
                    bool AllOperandsAreRegisters = true;
                    // Make sure all phi operands are X86 registers.
                    //
                    for (unsigned int OpIndex = 0; OpIndex < PHI->getNumIncomingValues(); OpIndex++)
                    {
                        if (!ValidateOperand(PHI->getOperand(OpIndex)))
                        {
                            AllOperandsAreRegisters = false;
                        }
                    }
                    if (AllOperandsAreRegisters)
                    {
                        ToRemove.push_back(Store);
                    }
                }
                else if (auto Select = llvm::dyn_cast<llvm::SelectInst>(Store->getPointerOperand()))
                {
                    if (ValidateOperand(Select->getOperand(1)) && ValidateOperand(Select->getOperand(2)))
                    {
                        ToRemove.push_back(Store);
                    }
                }
            }
        }

        for (auto Store : ToRemove)
        {
            // logger::warn("Removing {} with argument {}", ValueToString(Store), ValueToString(Store->getPointerOperand()));
            Store->eraseFromParent();
        }
    }

    return llvm::PreservedAnalyses::none();
}
