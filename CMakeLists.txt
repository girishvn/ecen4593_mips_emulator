cmake_minimum_required(VERSION 3.6)
project(ecen4593_mips_emulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp _decode.cpp _decode.h _instruction.h)
add_executable(ecen4593_mips_emulator ${SOURCE_FILES})