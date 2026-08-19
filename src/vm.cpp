#include "vm.hpp"
#include "utils.hpp"
#include "optimizer.hpp"
#include "logger.hpp"

#include <llvm/IR/InstIterator.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <remill/BC/Util.h>
#include <remill/BC/Optimizer.h>

#include <llvm/ADT/Statistic.h>
#include <llvm/Linker/Linker.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Transforms/IPO/AlwaysInliner.h>

llvm::cl::opt<std::string> Intrinsics("intrinsics",
    llvm::cl::desc("Path to the intrinsics.ll file"),
    llvm::cl::value_desc("Intrinsics filepath"),
    llvm::cl::Required);

llvm::cl::opt<uint64_t> HandlersVirtualAddress("handlers-va",
    llvm::cl::desc("Virtual address of the handlers array"),
    llvm::cl::value_desc("handlers va"),
    llvm::cl::Required);

llvm::cl::opt<uint64_t> HandlersCount("handlers-count",
    llvm::cl::desc("Total number of handlers"),
    llvm::cl::value_desc("handlers count"),
    llvm::cl::init(0x800),
    llvm::cl::Optional);

namespace vm
{
VM::VM(const std::filesystem::path& Binary)
    : EntryKey(0)
{
    MemoryManager = std::make_unique<binary::MemoryManager>(Binary);

    fassert(MemoryManager->getArchType() == llvm::Triple::ArchType::x86_64);
    fassert(MemoryManager->getObjectFormatType() == llvm::Triple::ObjectFormatType::COFF);

    Arch = remill::Arch::Get(Context, remill::OSName::kOSWindows, remill::ArchName::kArchAMD64);

    SemanticsModule = remill::LoadArchSemantics(Arch.get());
    HandlersModule  = std::make_unique<llvm::Module>("HandlersModule", Context);
    OutputModule    = std::make_unique<llvm::Module>("OutputModule", Context);

    Lifter = std::make_unique<binary::Lifter>();

    // Fill handlers array.
    //
    for (size_t i = 0; i < HandlersCount.getValue(); i++)
    {
        auto HandlerAddress = MemoryManager->getPointer(HandlersVirtualAddress.getValue() + i * 8).value();
        Handlers.push_back(HandlerAddress);
    }

    llvm::SMDiagnostic Error;
    if (auto IntrinsicsModule = llvm::parseIRFile(Intrinsics, Error, Context))
    {
        llvm::Linker::linkModules(*HandlersModule, std::move(IntrinsicsModule));
    }
    else
    {
        logger::error("Failed to parse intrinsics file");
    }

    HelperVirtualFunction = HandlersModule->getFunction("__warbird_vm");
    HelperVirtualStub     = HandlersModule->getFunction("__warbird_stub");
    HelperRetainValue     = HandlersModule->getFunction("__warbird_retain_value");

    if (HelperVirtualFunction == nullptr)
    {
        logger::error("No __warbird_vm function found");
    }
    if (HelperVirtualStub == nullptr)
    {
        logger::error("No __warbird_stub function found");
    }
    if (HelperRetainValue == nullptr)
    {
        logger::error("No __warbird_retain_value function found");
    }
}

llvm::Function* VM::createStubFunction(const std::string& Name)
{
    auto function = llvm::Function::Create(HelperVirtualStub->getFunctionType(), llvm::GlobalValue::LinkageTypes::ExternalLinkage, Name, HandlersModule.get());
    // Overwrite all attributes with only neccessery ones.
    // NOTE: This actually breaks optimizations. Some attributes added by clang compiler to intrinsics functions
    // break everything up!!!
    //
    function->setAttributes(llvm::AttributeList());
    function->addFnAttr(llvm::Attribute::AlwaysInline);
    function->addParamAttr(0, llvm::Attribute::NoAlias);
    function->addParamAttr(1, llvm::Attribute::NoAlias);
    return function;
}

llvm::Function* VM::lift(key_t Key)
{
    EntryKey = Key;
    // Lift from entry.
    //
    descent(Key);

    auto VirtualFunction = buildVirtualFunction();

    SaveIR(VirtualFunction->getParent(), "pre-result.ll");

    Optimizer(VirtualFunction)
        .stripSymbolNames(true)
        .inlineFunctionCalls(true)
        .exhaustOptimizations(true)
        .inlineMemoryIntrinsics(true)
        .enableInstCombineSpecificPass(true)
        .enableMemoryConcretizationPass(true, MemoryManager.get())
        .run();

    Optimizer(VirtualFunction)
        .exhaustOptimizations(true)
        .enableVirtualStackLifterPass(true)
        .enableMemoryConcretizationPass(true, MemoryManager.get())
        .run();

    Optimizer(VirtualFunction)
        .enableMemoryRemoverPass(true)
        .run();

    remill::MoveFunctionIntoModule(VirtualFunction, OutputModule.get());

    return VirtualFunction;
}

std::shared_ptr<Handler> VM::getHandler(key_t Key)
{
    auto Address = Handlers[Key & (Handlers.size() - 1)];

    auto LiftedFunction = Lifter->lift(Arch.get(), SemanticsModule.get(), MemoryManager.get(), Address);

    remill::OptimizeModule(Arch.get(), SemanticsModule.get(), { LiftedFunction });
    remill::MoveFunctionIntoModule(LiftedFunction, HandlersModule.get());

    Optimizer(LiftedFunction)
        .run();

    // Concretize key register.
    //
    StoreRegister(X86RegisterNumber::RDX, Key, LiftedFunction->getEntryBlock().getFirstInsertionPt());

    Optimizer(LiftedFunction)
        .inlineFunctionCalls(true)
        .exhaustOptimizations(true)
        .enableStackLifterPass(true)
        .enableStateRemoverPass(true, StateRemoveStrategy::CreateStore)
        .run();

    Optimizer(LiftedFunction)
        .exhaustOptimizations(true)
        .enableUndefRemoverPass(true)
        .run();

    Optimizer(LiftedFunction)
        .exhaustOptimizations(true)
        .enableStateRemoverPass(true, StateRemoveStrategy::RemoveStore)
        .run();

    // Make sure there's only 2 user of State (RAX and RCX).
    //
    auto State = remill::NthArgument(LiftedFunction, remill::kStatePointerArgNum);
    if (State->getNumUses() > 2)
    {
        SaveIR(LiftedFunction, "error-handler.ll");
        logger::error("More than 2 users of State found");
    }
    // Copy function body into a new function with proper signature.
    //
    auto HandlerFunction = createStubFunction(fmt::format("Handler.0x{:x}.0x{:x}", Key, Address));

    auto TryUpdateIntrinsic = [&](llvm::CallInst* Call, llvm::Value* Address, llvm::Value* Argument)
    {
        if (auto Load = llvm::dyn_cast<llvm::LoadInst>(Address))
        {
            if (GetRegisterByGetElementPtr(Load->getPointerOperand()) == X86RegisterNumber::RCX)
            {
                Call->setOperand(0, Load->getPointerOperand());
                Call->setOperand(1, Argument);
                return true;
            }
        }
        return false;
    };

    // We assume that after all the optimizations there's only 1 store to rax register and only 1 return instruction.
    //
    llvm::Value* Rax      = nullptr;
    llvm::ReturnInst* Ret = nullptr;

    llvm::ValueToValueMapTy Vm;

    Vm[remill::NthArgument(LiftedFunction, remill::kMemoryPointerArgNum)] = GetFunctionArgument(HandlerFunction, HandlerFunctionArgument::Memory);
    // 1. Create basic blocks and fill with instructions.
    //
    for (auto& Block : *LiftedFunction)
    {
        auto NewBlock = llvm::BasicBlock::Create(LiftedFunction->getContext(), Block.getName(), HandlerFunction);
        for (auto& Instruction : Block)
        {
            auto Store = llvm::dyn_cast<llvm::StoreInst>(&Instruction);
            auto GEP   = llvm::dyn_cast<llvm::GEPOperator>(&Instruction);
            auto Call  = llvm::dyn_cast<llvm::CallInst>(&Instruction);

            // Get value that is being stored in rax. This value will be returned in a new function.
            //
            if (Store && GetRegisterByGetElementPtr(Store->getPointerOperand()) == X86RegisterNumber::RAX)
            {
                if (Rax != nullptr)
                {
                    llvm::report_fatal_error("rax register is already set");
                }
                Rax = Store->getValueOperand();
                continue;
            }
            // Skip getelementptr to get rid of X86State.
            //
            else if (GEP && GEP->getPointerOperand() == State)
            {
                continue;
            }
            // Convert `Memory` argument in __remill_read_* to `Context` argument if it reads from RCX
            //
            else if (Call && Call->getCalledFunction()->getName().starts_with("__remill_read"))
            {
                auto Address = Call->getOperand(1);
                auto ConstantZero = llvm::ConstantInt::get(llvm::IntegerType::getInt64Ty(Context), 0);
                // uint8_t __remill_read_memory_8(rptr memory, uint64_t addr)
                if (!TryUpdateIntrinsic(Call, Address, ConstantZero))
                {
                    if (auto Add = llvm::dyn_cast<llvm::AddOperator>(Address))
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            if (TryUpdateIntrinsic(Call, Add->getOperand(i), Add->getOperand(i ^ 1)))
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else if (Call && Call->getCalledFunction()->getName().starts_with("__remill_write"))
            {
                auto Address = Call->getOperand(1);
                auto ConstantZero = llvm::ConstantInt::get(llvm::IntegerType::getInt64Ty(Context), 0);
                // rptr __remill_write_memory_8(rptr memory, uint64_t addr, uint8_t value)
                if (!TryUpdateIntrinsic(Call, Address, ConstantZero))
                {
                    if (auto Add = llvm::dyn_cast<llvm::AddOperator>(Address))
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            if (TryUpdateIntrinsic(Call, Add->getOperand(i), Add->getOperand(i ^ 1)))
                            {
                                break;
                            }
                        }
                    }
                }
            }
            // Copy instruction into a new block.
            //
            auto Copy = Instruction.clone();
            Copy->insertInto(NewBlock, NewBlock->end());
            Vm[&Instruction] = Copy;
            if (llvm::isa<llvm::ReturnInst>(Copy))
                Ret = llvm::dyn_cast<llvm::ReturnInst>(Copy);
        }
        Vm[&Block] = NewBlock;
    }
    // 2. Fix instruction references.
    //
    for (auto& Instruction : llvm::instructions(*LiftedFunction))
    {
        if (!Vm.count(&Instruction))
            continue;

        auto NewInstruction = llvm::dyn_cast<llvm::Instruction>(Vm[&Instruction]);

        for (auto& Operand : NewInstruction->operands())
        {
            if (Vm.count(Operand.get()))
            {
                Operand.set(Vm[Operand.get()]);
            }
            // Replace RCX with function argument.
            //
            else if (GetRegisterByGetElementPtr(Operand.get()) == X86RegisterNumber::RCX)
            {
                Operand.set(GetFunctionArgument(HandlerFunction, HandlerFunctionArgument::Context));
            }
        }
        // Fix phi nodes to point to the new blocks.
        //
        if (auto PHI = llvm::dyn_cast<llvm::PHINode>(NewInstruction))
        {
            for (unsigned i = 0; i < PHI->getNumIncomingValues(); i++)
            {
                PHI->setIncomingBlock(i, llvm::dyn_cast<llvm::BasicBlock>(Vm[PHI->getIncomingBlock(i)]));
            }
        }
    }
    // 3. Set return value.
    //
    if (Vm.count(Rax))
    {
        Ret->setOperand(0, Vm[Rax]);
    }
    else
    {
        Ret->setOperand(0, Rax);
    }

    Optimizer(HandlerFunction)
        .exhaustOptimizations(true)
        .inlineFunctionCalls(true)
        .inlineMemoryIntrinsics(true)
        .run();

    // Get successors of this handler.
    //
    auto ReturnedValue = Ret->getOperand(0);

    std::vector<key_t> Successors;

    if (auto Constant = llvm::dyn_cast<llvm::ConstantInt>(ReturnedValue))
    {
        Successors.push_back(Constant->getLimitedValue());
    }
    else if (auto Select = llvm::dyn_cast<llvm::SelectInst>(ReturnedValue))
    {
        Successors.push_back(llvm::dyn_cast<llvm::ConstantInt>(Select->getTrueValue())->getLimitedValue());
        Successors.push_back(llvm::dyn_cast<llvm::ConstantInt>(Select->getFalseValue())->getLimitedValue());
    }
    else if (auto PHI = llvm::dyn_cast<llvm::PHINode>(ReturnedValue))
    {
        for (unsigned ValueIndex = 0; ValueIndex < PHI->getNumIncomingValues(); ValueIndex++)
        {
            if (auto Constant = llvm::dyn_cast<llvm::ConstantInt>(PHI->getIncomingValue(ValueIndex)))
            {
                Successors.push_back(Constant->getLimitedValue());
            }
            else if (auto Select = llvm::dyn_cast<llvm::SelectInst>(PHI->getIncomingValue(ValueIndex)))
            {
                Successors.push_back(llvm::dyn_cast<llvm::ConstantInt>(Select->getTrueValue())->getLimitedValue());
                Successors.push_back(llvm::dyn_cast<llvm::ConstantInt>(Select->getFalseValue())->getLimitedValue());
            }
            else
            {
                logger::warn("Unsupported return value inside PHI node found in {}", HandlerFunction->getName().str());
            }
        }
    }
    else
    {
        SaveIR(HandlerFunction, fmt::format("{}.ll", HandlerFunction->getName().str()));
        logger::warn("Unsupported return value found in {}... Probably just vm exit", HandlerFunction->getName().str());
    }

    LiftedFunction->eraseFromParent();

    return std::make_shared<Handler>(HandlerFunction, std::move(Successors));
}

llvm::Function* VM::buildVirtualFunction(key_t Target)
{
    auto Function = createStubFunction("__warbird_vm");
    auto Entry    = llvm::BasicBlock::Create(Context, "entry", Function);
    // Fill Function with the basic blocks from already lifted handlers.
    //
    std::unordered_map<key_t, llvm::BasicBlock*> Blocks;
    for (const auto& [Key, Handler] : LiftedHandlers)
    {
        Blocks.emplace(Key, llvm::BasicBlock::Create(Context, fmt::format("handler_0x{:x}", Key), Function));
    }
    // Link together llvm basic blocks based on successors of handlers and populate with the calls to handler functions.
    //
    llvm::IRBuilder<> IR(Context);
    for (auto& [Key, Block] : Blocks)
    {
        IR.SetInsertPoint(Block);
        const auto& Handler = LiftedHandlers.at(Key);
        auto Call = IR.CreateCall(Handler->Function, { Function->getArg(0), Function->getArg(1) });
        // Check if we are building a partial function and if so, make a call to __warbird_retain_value.
        //
        if (Key == Target)
        {
            Call = IR.CreateCall(HelperRetainValue, { Call });
        }
        const auto& Successors = Handler->GetSuccessors();
        // Link successors with the current block.
        //
        switch (Successors.size())
        {
        case 0:
        {
            IR.CreateRet(Call);
            break;
        }
        case 1:
        {
            IR.CreateBr(Blocks.at(Successors[0]));
            break;
        }
        case 2:
        {
            llvm::BasicBlock* Block0 = nullptr;
            llvm::BasicBlock* Block1 = nullptr;

            auto key0 = Successors[0];
            auto key1 = Successors[1];
            if (Blocks.contains(key0))
            {
                Block0 = Blocks.at(key0);
            }
            if (Blocks.contains(key1))
            {
                Block1 = Blocks.at(key1);
            }
            if (Block0 != nullptr && Block1 != nullptr)
            {
                IR.CreateCondBr(IR.CreateICmpEQ(Call, IR.getInt64(key0)), Block0, Block1);
            }
            else
            {
                fassert(Target != 0);
                IR.CreateBr(Block0 != nullptr ? Block0 : Block1);
            }
            break;
        }
        default:
            logger::error("Invalid number of successors: {} for handler 0x{:x}", Successors.size(), Handler->Function->getName());
            break;
        }
    }
    // Link entry block with the function body.
    //
    llvm::BranchInst::Create(Blocks.at(EntryKey), Entry);
    // Copy vm function and inject call to stub function.
    //
    llvm::ValueToValueMapTy Vm;
    auto VirtualFunction = llvm::CloneFunction(HelperVirtualFunction, Vm);
    for (auto& Instruction : llvm::instructions(VirtualFunction))
    {
        if (auto Call = llvm::dyn_cast<llvm::CallInst>(&Instruction))
        {
            if (Call->getCalledFunction() == HelperVirtualStub)
            {
                Call->setCalledFunction(Function);
            }
        }
    }
    Optimizer(VirtualFunction)
        .run();
    return VirtualFunction;
}

void VM::descent(key_t Key)
{
    if (LiftedHandlers.contains(Key))
    {
        return;
    }

    auto Handler = getHandler(Key);

    logger::info("lifting 0x{:016x} 0x{:x} {}", Key, Handlers[Key & (Handlers.size() - 1)], Handler->GetSuccessors().size());

    LiftedHandlers.emplace(Key, Handler);

    const auto& Successors = Handler->GetSuccessors();

    switch (Successors.size())
    {
    case 2:
    {
        descent(Successors[0]);
        descent(Successors[1]);
        break;
    }
    case 1:
    {
        descent(Successors[0]);
        break;
    }
    case 0:
    {
        // Build partial CFG for specified basic block and retain its return value.
        //
        auto VirtualFunction = buildVirtualFunction(Key);

        Optimizer(VirtualFunction)
            .exhaustOptimizations(true)
            .inlineFunctionCalls(true)
            .stripSymbolNames(true)
            .enableMemoryConcretizationPass(true, MemoryManager.get())
            .enableInstCombineSpecificPass(true)
            .run();

        SaveIR(VirtualFunction, fmt::format("slice.{}.ll", VirtualFunction->getName()));

        Optimizer(VirtualFunction)
            .enableVirtualStackLifterPass(true)
            .exhaustOptimizations(true)
            .run();

        // Get the call to __warbird_retain_value function.
        //
        for (auto& Instruction : llvm::instructions(VirtualFunction))
        {
            if (auto Call = llvm::dyn_cast<llvm::CallInst>(&Instruction))
            {
                if (Call->getCalledFunction() == HelperRetainValue)
                {
                    if (auto Constant = llvm::dyn_cast<llvm::ConstantInt>(Call->getOperand(0)))
                    {
                        auto Value = Constant->getZExtValue();
                        logger::warn("Return value is a constant 0x{:x}", Value);
                        Handler->AddSuccessor(Value);
                        descent(Value);
                    }
                    else
                    {
                        logger::warn("Symbolic return value found..");
                        SaveIR(Handler->Function, fmt::format("{}.ll", Handler->Function->getName()));
                    }
                }
            }
        }
        break;
    }
    default:
        logger::error("Invalid number of successors: {} for handler 0x{:x}", Successors.size(), Handler->Function->getName());
        break;
    }
}
};
