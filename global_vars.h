//
// Created by Girish Narayanswamy on 4/18/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H
#define ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H

#include "_IFID.h"
#include "_IDEX.h"
#include "_EXMEM.h"
#include "_MEMWB.h"

//Global Variables:

uint32_t register_bank[32]; //32-register system
uint32_t programCount; //program counter

//Intermediate Registers

_IFID IFID;
_IFID shadow_IFID;

_IDEX IDEX;
_IDEX shadow_IDEX;

_EXMEM EXMEM;
_EXMEM shadow_EXMEM;

_MEMWB MEMWB;
_MEMWB shadow_MEMWB;


#endif //ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H
