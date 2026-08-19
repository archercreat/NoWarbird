#include <cstring>
#include <cstdint>

using rptr = uint8_t* __restrict__;

extern "C" uint64_t __undef;

extern "C" uint64_t __warbird_retain_value(uint64_t value);
extern "C" uint64_t __attribute__((always_inline)) __warbird_stub(rptr context, rptr memory);

// This functions are used to prevent global variables from being optimized.
//
void __retain_pointers()
{
    __undef = 0;
    __warbird_retain_value(0);
    __warbird_stub(nullptr, nullptr);
}

extern "C"
{
// ci.dll
uint64_t __attribute__((always_inline)) __warbird_vm(rptr memory, volatile rptr vsp, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3)
{
    uint64_t context[56] = { 0 };

    context[8]   = arg0;
    context[5]   = arg1;
    context[39]  = arg2;
    context[18]  = arg3;
    context[49]  = (uint64_t)vsp;
    context[15]  = (uint64_t)vsp;
    //
    __warbird_stub(reinterpret_cast<rptr>(context), memory);
    // VM returns NTSTATUS from context register.
    //
    return context[49];
}

// ClipSp.sys
// uint64_t __attribute__((always_inline)) __warbird_vm(rptr memory, volatile rptr vsp, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4)
// {
//     uint64_t context[56] = { 0 };

//     std::memcpy(&vsp[40], &memory[arg4], 24);

//     context[48] = arg0;
//     context[17] = arg1;
//     context[26] = arg2;
//     context[21] = arg3;
//     context[9]  = (uint64_t)vsp;
//     context[45] = (uint64_t)vsp;
//     // Call lifted function.
//     //
//     __warbird_stub(reinterpret_cast<rptr>(context), memory);
//     // VM returns NTSTATUS from context register.
//     //
//     return context[45];
// }

// PEAuth.sys
// uint64_t __attribute__((always_inline)) __warbird_vm(rptr memory, volatile rptr vsp, uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3)
// {
//     uint64_t context[56] = { 0 };

//     context[30] = arg0;
//     context[25] = arg1;
//     context[44] = arg2;
//     context[11] = arg3;
//     context[41]  = (uint64_t)vsp;
//     context[54] = (uint64_t)vsp;
//     // Call lifted function.
//     //
//     __warbird_stub(reinterpret_cast<rptr>(context), memory);
//     // VM returns NTSTATUS from context register.
//     //
//     return context[41];
// }

uint8_t __remill_read_memory_8(rptr memory, uint64_t addr)
{
    uint8_t v{};
    std::memcpy(&v, &memory[addr], sizeof(v));
    return v;
}

uint16_t __remill_read_memory_16(rptr memory, uint64_t addr)
{
    uint16_t v{};
    std::memcpy(&v, &memory[addr], sizeof(v));
    return v;
}

uint32_t __remill_read_memory_32(rptr memory, uint64_t addr)
{
    uint32_t v{};
    std::memcpy(&v, &memory[addr], sizeof(v));
    return v;
}

uint64_t __remill_read_memory_64(rptr memory, uint64_t addr)
{
    uint64_t v{};
    std::memcpy(&v, &memory[addr], sizeof(v));
    return v;
}

// rptr __remill_read_memory_f80(rptr memory, uint64_t addr, native_float80_t& value)
// {
//     std::memcpy(&value, &__ram[addr], sizeof(value));
//     return memory;
// }

rptr __remill_write_memory_8(rptr memory, uint64_t addr, uint8_t value)
{
    std::memcpy(&memory[addr], &value, sizeof(value));
    return memory;
}

rptr __remill_write_memory_16(rptr memory, uint64_t addr, uint16_t value)
{
    std::memcpy(&memory[addr], &value, sizeof(value));
    return memory;
}

rptr __remill_write_memory_32(rptr memory, uint64_t addr, uint32_t value)
{
    std::memcpy(&memory[addr], &value, sizeof(value));
    return memory;
}

rptr __remill_write_memory_64(rptr memory, uint64_t addr, uint64_t value)
{
    std::memcpy(&memory[addr], &value, sizeof(value));
    return memory;
}

rptr __attribute__((always_inline)) __remill_barrier_load_load(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_barrier_load_store(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_barrier_store_load(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_barrier_store_store(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_atomic_begin(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_atomic_end(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_delay_slot_begin(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_delay_slot_end(rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_missing_block(rptr, uint64_t, rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_function_return(rptr, uint64_t, rptr memory)
{
    return memory;
}

rptr __attribute__((always_inline)) __remill_jump(rptr, uint64_t, rptr memory)
{
    return memory;
}

uint8_t __attribute__((always_inline)) __remill_undefined_8(void)
{
    return 0;
}

uint16_t __attribute__((always_inline)) __remill_undefined_16(void)
{
    return 0;
}

uint32_t __attribute__((always_inline)) __remill_undefined_32(void)
{
    return 0;
}

uint64_t __attribute__((always_inline)) __remill_undefined_64(void)
{
    return 0;
}

rptr __attribute__((always_inline)) __remill_compare_exchange_memory_32(rptr memory, uint64_t addr, uint32_t& expected, uint32_t desired)
{
    expected = __sync_val_compare_and_swap(&memory[addr], expected, desired);
    return memory;
}

// float32_t __attribute__((always_inline)) __remill_undefined_f32(void)
// {
//     return 0.0;
// }

// float64_t __attribute__((always_inline)) __remill_undefined_f64(void)
// {
//     return 0.0;
// }

// float80_t __attribute__((always_inline)) __remill_undefined_f80(void)
// {
//     return {0};
// }

bool __attribute__((always_inline)) __remill_flag_computation_zero(bool result, ...)
{
    return result;
}

bool __attribute__((always_inline)) __remill_flag_computation_sign(bool result, ...)
{
    return result;
}

bool __attribute__((always_inline)) __remill_flag_computation_overflow(bool result, ...)
{
    return result;
}

bool __attribute__((always_inline)) __remill_flag_computation_carry(bool result, ...)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_sle(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_slt(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_sge(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_sgt(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_ule(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_ult(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_ugt(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_uge(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_eq(bool result)
{
    return result;
}

bool __attribute__((always_inline)) __remill_compare_neq(bool result)
{
    return result;
}
}
