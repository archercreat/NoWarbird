#pragma once
#include <llvm/IR/Module.h>
#include <llvm/IR/Operator.h>
#include <llvm/IR/Instructions.h>

#include <remill/Arch/X86/Runtime/State.h>

void SaveIR(llvm::Value* value,   const std::string& filename);
void SaveIR(llvm::Module* module, const std::string& filename);

enum X86RegisterNumber
{
    INVALID = 0,
    CF      = offsetof(X86State, aflag.cf),
    PF      = offsetof(X86State, aflag.pf),
    AF      = offsetof(X86State, aflag.af),
    ZF      = offsetof(X86State, aflag.zf),
    SF      = offsetof(X86State, aflag.sf),
    DF      = offsetof(X86State, aflag.df),
    OF      = offsetof(X86State, aflag.of),
    RAX     = offsetof(X86State, gpr.rax),
    RBX     = offsetof(X86State, gpr.rbx),
    RCX     = offsetof(X86State, gpr.rcx),
    RDX     = offsetof(X86State, gpr.rdx),
    RSI     = offsetof(X86State, gpr.rsi),
    RDI     = offsetof(X86State, gpr.rdi),
    RSP     = offsetof(X86State, gpr.rsp),
    RBP     = offsetof(X86State, gpr.rbp),
    R8      = offsetof(X86State, gpr.r8),
    R9      = offsetof(X86State, gpr.r9),
    R10     = offsetof(X86State, gpr.r10),
    R11     = offsetof(X86State, gpr.r11),
    R12     = offsetof(X86State, gpr.r12),
    R13     = offsetof(X86State, gpr.r13),
    R14     = offsetof(X86State, gpr.r14),
    R15     = offsetof(X86State, gpr.r15),
    RIP     = offsetof(X86State, gpr.rip),
    RFLAGS  = offsetof(X86State, rflag)
};

/// Function arguments in the VM function.
///
enum class MainFunctionArgument
{
    Memory,
    VSP,
    Arg1,
    Arg2,
    Arg3,
    Arg4,
    Arg5 // This arg is only present in clipsp.sys
};

enum class HandlerFunctionArgument
{
    Context,
    Memory
};

std::string ValueToString(llvm::Value* Value);

llvm::Argument* GetFunctionArgument(llvm::Function* Function, MainFunctionArgument Argument);
llvm::Argument* GetFunctionArgument(llvm::Function* Function, HandlerFunctionArgument Argument);

X86RegisterNumber GetRegisterByGetElementPtr(llvm::Value* value);

llvm::Value* LoadRegister(X86RegisterNumber Register, llvm::BasicBlock* InsertPoint);

void StoreRegister(X86RegisterNumber Register, uint64_t Value, llvm::BasicBlock* InsertPoint);
void StoreRegister(X86RegisterNumber Register, llvm::Value* Value, llvm::BasicBlock* InsertPoint);
void StoreRegister(X86RegisterNumber Register, uint64_t Value, llvm::BasicBlock::iterator InsertPoint);

llvm::SmallVector<llvm::CallInst*> GetMemoryReads(llvm::Function& Function);
llvm::SmallVector<llvm::CallInst*> GetMemoryWrites(llvm::Function& Function);

// Bunch of getters.
//
llvm::GlobalVariable* GetGlobalRamVariable(llvm::Module* Module);
llvm::GlobalVariable* GetGlobalContextVariable(llvm::Module* Module);
llvm::GlobalVariable* GetGlobalUndefVariable(llvm::Module* Module);
