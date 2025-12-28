#include <cstdlib>

#include <glog/logging.h>
#include <remill/Arch/Arch.h>
#include <remill/Arch/Instruction.h>
#include <remill/Arch/Name.h>
#include <remill/BC/ABI.h>
#include <remill/BC/IntrinsicTable.h>
#include <remill/BC/Lifter.h>
#include <remill/BC/Optimizer.h>
#include <remill/BC/Util.h>
#include <remill/BC/Version.h>
#include <remill/OS/OS.h>
#include <remill/Version/Version.h>

#include <llvm/Demangle/Demangle.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Transforms/IPO/GlobalDCE.h>

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);

  llvm::LLVMContext context;
  auto arch = remill::Arch::Get(context, "linux", "amd64");
  if (!arch) {
    llvm::outs() << "Failed to get architecture\n";
    return EXIT_FAILURE;
  }

  auto semantics = remill::LoadArchSemantics(arch.get());
  if (!semantics) {
    llvm::outs() << "Failed to load architecture semantics\n";
    return EXIT_FAILURE;
  }

  auto intrinsics = arch->GetInstrinsicTable();
  if (!intrinsics) {
    llvm::outs() << "Failed to get intrinsic table\n";
    return EXIT_FAILURE;
  }

  // mov rcx, 1337
  uint8_t instr_bytes[] = {0x48, 0xc7, 0xc1, 0x39, 0x05, 0x00, 0x00};
  std::string_view instr_view(reinterpret_cast<char *>(instr_bytes),
                              sizeof(instr_bytes));
  remill::Instruction instruction;
  remill::DecodingContext decoding_context = arch->CreateInitialContext();
  if (!arch->DecodeInstruction(0x1000, instr_view, instruction,
                               decoding_context)) {
    llvm::outs() << "Failed to decode instruction\n";
    return EXIT_FAILURE;
  }

  auto function = arch->DefineLiftedFunction("lifted_example", semantics.get());
  auto block = &function->getEntryBlock();
  auto lifter = instruction.GetLifter();
  auto status = lifter->LiftIntoBlock(instruction, block);
  if (status != remill::kLiftedInstruction) {
    llvm::outs() << "Failed to lift instruction\n";
    return EXIT_FAILURE;
  }

  // Finish the lifted block by returning the memory pointer.
  llvm::IRBuilder<> ir(block);
  ir.CreateRet(remill::LoadMemoryPointer(block, *intrinsics));

  // Print called functions
  llvm::outs() << "[unoptimized]\n";
  auto printed = std::set<llvm::Function *>{};
  for (auto &basic_block : *function) {
    for (auto &instruction : basic_block) {
      if (auto caller = llvm::dyn_cast<llvm::CallBase>(&instruction)) {
        auto callee = caller->getCalledFunction();
        if (!printed.count(callee)) {
          auto name = callee->getName().str();
          llvm::outs() << "; Mangled name: " << name << "\n";
          callee->setName(llvm::demangle(name));
          llvm::outs() << *callee << "\n";
          printed.insert(callee);
        }
      }
    }
  }
  function->print(llvm::outs());

  remill::OptimizeModule(arch.get(), semantics.get(), {function});

  llvm::outs() << "\n[optimized]\n";
  function->print(llvm::outs());

  return EXIT_SUCCESS;
}
