#include "utils.hpp"
#include "logger.hpp"

#include <map>
#include <vector>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstIterator.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <remill/BC/Util.h>

void SaveIR(llvm::Value* value, const std::string& filename)
{
    std::error_code ec;
    llvm::raw_fd_ostream fd(filename, ec);
    value->print(fd, false);
}

void SaveIR(llvm::Module* module, const std::string& filename)
{
    std::error_code ec;
    llvm::raw_fd_ostream fd(filename, ec);
    module->print(fd, nullptr);
}

std::string ValueToString(llvm::Value* Value)
{
    std::string Buffer;
    llvm::raw_string_ostream OS(Buffer);

    Value->print(OS);

    return Buffer;
}

llvm::Argument* GetFunctionArgument(llvm::Function* Function, MainFunctionArgument Argument)
{
    return Function->getArg(static_cast<int>(Argument));
}

llvm::Argument* GetFunctionArgument(llvm::Function* Function, HandlerFunctionArgument Argument)
{
    return Function->getArg(static_cast<int>(Argument));
}

X86RegisterNumber GetRegisterByGetElementPtr(llvm::Value* Value)
{
    if (auto GEP = llvm::dyn_cast<llvm::GEPOperator>(Value))
    {
        if (GEP->hasAllConstantIndices())
        {
            const auto Index = llvm::dyn_cast<llvm::ConstantInt>(GEP->indices().begin()->get())->getValue().getLimitedValue();
            // Check if an index is in bounds.
            //
            if (Index >= X86RegisterNumber::CF && Index <= X86RegisterNumber::RIP)
            {
                return static_cast<X86RegisterNumber>(Index);
            }
        }
    }
    return X86RegisterNumber::INVALID;
}

llvm::SmallVector<llvm::CallInst*> GetMemoryReads(llvm::Function& Function)
{
    llvm::SmallVector<llvm::CallInst*> Calls;
    for (auto& Instruction : llvm::instructions(Function))
    {
        if (auto Call = llvm::dyn_cast<llvm::CallInst>(&Instruction))
        {
            if (Call->getCalledFunction()->getName().starts_with("__remill_read"))
                Calls.push_back(Call);
        }
    }
    return Calls;
}

llvm::SmallVector<llvm::CallInst*> GetMemoryWrites(llvm::Function& Function)
{
    llvm::SmallVector<llvm::CallInst*> Calls;

    for (auto& Instruction : llvm::instructions(Function))
    {
        if (auto Call = llvm::dyn_cast<llvm::CallInst>(&Instruction))
        {
            if (Call->getCalledFunction()->getName().starts_with("__remill_write"))
                Calls.push_back(Call);
        }
    }
    return Calls;
}

llvm::Value* LoadRegister(X86RegisterNumber Register, llvm::BasicBlock* InsertPoint)
{
    auto Function = InsertPoint->getParent();

    llvm::IRBuilder<> IR(InsertPoint);

    auto StateArgument = remill::NthArgument(Function, remill::kStatePointerArgNum);
    auto RegisterType = Register >= X86RegisterNumber::RAX ? IR.getInt64Ty() : IR.getInt8Ty();
    return IR.CreateLoad(
        RegisterType,
        IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(Register) })
    );
}

void StoreRegister(X86RegisterNumber Register, uint64_t Value, llvm::BasicBlock* InsertPoint)
{
    auto BitCount = Register >= X86RegisterNumber::RAX ? 64 : 8;

    StoreRegister(
        Register,
        llvm::ConstantInt::get(llvm::IntegerType::get(InsertPoint->getContext(), BitCount), Value),
        InsertPoint
    );
}

void StoreRegister(X86RegisterNumber Register, llvm::Value* Value, llvm::BasicBlock* InsertPoint)
{
    auto Function = InsertPoint->getParent();

    llvm::IRBuilder<> IR(InsertPoint);

    auto StateArgument = remill::NthArgument(Function, remill::kStatePointerArgNum);
    IR.CreateStore(
        Value,
        IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(Register) })
    );
}

void StoreRegister(X86RegisterNumber Register, uint64_t Value, llvm::BasicBlock::iterator InsertPoint)
{
    auto BitCount = Register >= X86RegisterNumber::RAX ? 64 : 8;
    auto Function = InsertPoint->getFunction();

    llvm::IRBuilder<> IR(InsertPoint->getContext());
    IR.SetInsertPoint(InsertPoint);

    auto StateArgument = remill::NthArgument(Function, remill::kStatePointerArgNum);
    IR.CreateStore(
        llvm::ConstantInt::get(llvm::IntegerType::get(InsertPoint->getContext(), BitCount), Value),
        IR.CreateInBoundsGEP(IR.getInt8Ty(), StateArgument, { IR.getInt64(Register) })
    );
}

void ConcretizeRegister(llvm::Function* Function, X86RegisterNumber Register, uint64_t Value)
{
    llvm::IRBuilder<> IR(Function->getContext());

    IR.SetInsertPoint(Function->getEntryBlock().getFirstInsertionPt());

    IR.CreateStore(
        IR.getInt64(Value),
        IR.CreateInBoundsGEP(IR.getInt8Ty(), Function->getArg(0), {IR.getInt64(Register)})
    );
}

llvm::GlobalVariable* GetGlobalRamVariable(llvm::Module* Module)
{
    if (auto RAM = Module->getGlobalVariable("__ram"))
    {
        return RAM;
    }
    return Module->getOrInsertGlobal("__ram", llvm::ArrayType::get(llvm::IntegerType::get(Module->getContext(), 8), 0));
}

llvm::GlobalVariable* GetGlobalContextVariable(llvm::Module* Module)
{
    if (auto Context = Module->getGlobalVariable("__context"))
    {
        return Context;
    }
    return Module->getOrInsertGlobal("__context", llvm::ArrayType::get(llvm::IntegerType::get(Module->getContext(), 8), 0));
}

llvm::GlobalVariable* GetGlobalUndefVariable(llvm::Module* Module)
{
    if (auto Undef = Module->getGlobalVariable("__undef"))
    {
        return Undef;
    }
    return Module->getOrInsertGlobal("__undef", llvm::IntegerType::getInt64Ty(Module->getContext()));
}
