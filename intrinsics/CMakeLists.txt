cmake_minimum_required(VERSION 3.21)

project(intrinsics)

set(CMAKE_CXX_COMPILER "clang++")

set(HELPER_CLANG_FLAGS
    -std=c++17
    -O1
    -disable-llvm-passes
    -Wno-gnu-inline-cpp-without-extern
    -fno-discard-value-names
    -fstrict-aliasing
    -fno-slp-vectorize
    -mllvm
    -enable-tbaa=true
    -emit-llvm
    -I ${REMILL_PATH}
)

set(SOURCES src/main.cpp)

add_custom_command(OUTPUT
    "${CMAKE_CURRENT_BINARY_DIR}/intrinsics.ll"
    COMMAND "${CMAKE_CXX_COMPILER}" ${HELPER_CLANG_FLAGS} -DADDRESS_SIZE_BITS=64 -m64 -S src/main.cpp -o intrinsics.ll
    MAIN_DEPENDENCY ${SOURCES}
    DEPENDS ${SOURCES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_custom_target(${PROJECT_NAME} ALL
    DEPENDS intrinsics.ll
    SOURCES ${SOURCES}
)