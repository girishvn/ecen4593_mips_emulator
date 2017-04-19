cmake_minimum_required(VERSION 3.6)
project(ecen4593_mips_emulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        decode.cpp
        decode.h
        Execute.cpp
        Execute.h
        main.cpp
        README.md intermediate_reg_structs.h global_vars.cpp global_vars.h)

add_executable(ecen4593_mips_emulator ${SOURCE_FILES})