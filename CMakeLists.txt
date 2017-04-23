cmake_minimum_required(VERSION 3.6)
project(ecen4593_mips_emulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        fetch.cpp
        fetch.h
        decode.cpp
        decode.h
        Execute.cpp
        Execute.h
        global_vars.cpp
        global_vars.h
        intermediate_reg_structs.h
        Load_Program.c
        Load_Program.h
        main.cpp Memory.h Memory.cpp WriteBack.h WriteBack.cpp)

add_executable(ecen4593_mips_emulator ${SOURCE_FILES})