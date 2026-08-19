#pragma once
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

#include <type_traits>

#ifdef _MSC_VER
    #include <intrin.h>
    #define unreachable() __assume(0)
#else
    #include <emmintrin.h>
    #include <x86intrin.h>
    #define unreachable() __builtin_unreachable()
#endif

namespace logger
{
static void debug(const char* format, auto... args)
{
    fmt::print(fg(fmt::color::dark_orange) | fmt::emphasis::bold, "[DEBUG] ");
    fmt::print(fmt::runtime(format), args...);
    fmt::print("\n");
}

static void info(const char* format, const auto&... args)
{
    fmt::print(fg(fmt::color::cadet_blue) | fmt::emphasis::bold, "[INFO]  ");
    fmt::print(fmt::runtime(format), args...);
    fmt::print("\n");
}

static void warn(const char* format, const auto&... args)
{
    fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold, "[WARN]  ");
    fmt::print(fmt::runtime(format), args...);
    fmt::print("\n");
}

static void error [[noreturn]](const char* format, const auto&... args)
{
    fmt::print(fg( fmt::color::red) | fmt::emphasis::bold, "[ERROR] ");
    fmt::print(fmt::runtime(format), args...);
    fmt::print("\n");
    throw -1;
}
};

static constexpr void abort_if(bool condition, const char* string)
{
    if (condition)
    {
        if (std::is_constant_evaluated())
            throw std::logic_error(string);
        else
            logger::error("Assertion failure, {}", string);
    }
}

#define fassert__stringify(x) #x
#define fassert__istringify(x) fassert__stringify(x)
#define fassert(...) abort_if(!bool(__VA_ARGS__), fassert__stringify(__VA_ARGS__) " at " __FILE__ ":" fassert__istringify(__LINE__) )
