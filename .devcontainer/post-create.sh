#!/bin/bash
# Configure CMake project
rm -rf build
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Install gdb
apt update
apt install -y gdb
