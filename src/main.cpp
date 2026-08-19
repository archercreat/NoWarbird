#include "vm.hpp"
#include "utils.hpp"
#include "logger.hpp"
#include "optimizer.hpp"

#include <fstream>
#include <llvm/ADT/Statistic.h>

#include <llvm/Support/Signals.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/PrettyStackTrace.h>

#include <remill/BC/Util.h>
#include <remill/BC/Optimizer.h>

llvm::cl::opt<std::string> Binary("binary",
    llvm::cl::desc("Path to the target Binary"),
    llvm::cl::value_desc("Binary"),
    llvm::cl::Required);

llvm::cl::opt<uint64_t> Key("key",
    llvm::cl::desc("Initial key value for virtual machine"),
    llvm::cl::value_desc("key"),
    llvm::cl::Required);

static const std::vector<const char*> OptimizationArguments =
{
    "-memdep-block-scan-limit=99999999",
    "-rotation-max-header-size=99999999",
    "-earlycse-mssa-optimization-cap=99999999",
    "-dse-memoryssa-defs-per-block-limit=99999999",
    "-dse-memoryssa-partial-store-limit=99999999",
    "-dse-memoryssa-path-check-limit=99999999",
    "-dse-memoryssa-scanlimit=99999999",
    "-dse-memoryssa-walklimit=99999999",
    "-dse-memoryssa-otherbb-cost=2",
    "-memssa-check-limit=99999999",
    "-memdep-block-number-limit=99999999",
    "-memdep-block-scan-limit=99999999",
    "-gvn-max-block-speculations=99999999",
    "-gvn-max-num-deps=99999999",
    "-gvn-max-num-insns=99999999",
    "-gvn-hoist-max-chain-length=-1",
    "-gvn-hoist-max-depth=-1",
    "-gvn-hoist-max-bbs=-1",
    "-unroll-threshold=99999999",
    "-instcombine-max-sink-users=99999999",
    "-instcombine-max-copied-from-constant-users=99999999",
    "-instcombine-maxarray-size=99999999",
    "-enable-gvn-hoist",
    "-enable-gvn-sink",
    "-constraint-elimination-max-rows=9999999"
};

int main(int argc, char** argv)
{
    // Inject optimization options to argv.
    //
    std::vector<const char*> Args;
    std::copy_n(argv, argc, std::back_inserter(Args));
    std::copy(OptimizationArguments.begin(), OptimizationArguments.end(), std::back_inserter(Args));
    // Enable stack traces.
    //
    llvm::sys::PrintStackTraceOnErrorSignal(Args[0]);
    llvm::PrettyStackTraceProgram X(Args.size(), Args.data());
    // Parse command parameters.
    //
    llvm::cl::ParseCommandLineOptions(Args.size(), Args.data());

    auto VM = vm::VM(Binary.getValue());

    auto LiftedFunction = VM.lift(Key.getValue());

    SaveIR(LiftedFunction->getParent(), "result.ll");

    llvm::PrintStatistics();

    return 0;
}
