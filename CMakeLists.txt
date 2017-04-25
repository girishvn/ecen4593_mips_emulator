cmake_minimum_required(VERSION 3.6)
project(ecen4593_mips_emulator)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        global_vars.cpp
        global_vars.h
        Fetch.cpp
        Fetch.h
        Decode.cpp
        Decode.h
        Execute.cpp
        Execute.h
        Memory.cpp
        Memory.h
        WriteBack.cpp
        WriteBack.h
        main.cpp
        Load_Insts.cpp
        Load_Insts.h)

add_executable(ecen4593_mips_emulator ${SOURCE_FILES})