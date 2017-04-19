//
// Created by Girish Narayanswamy on 4/19/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H
#define ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H

#include <cstdint>
#include "intermediate_reg_structs.h"

//Global Variables:

extern uint32_t register_bank[32]; //32-register system
extern uint32_t programCount; //program counter

//Intermediate Registers

extern _IFID IFID;
extern _IFID shadow_IFID;

extern _IDEX IDEX;
extern _IDEX shadow_IDEX;

extern _EXMEM EXMEM;
extern _EXMEM shadow_EXMEM;

extern _MEMWB MEMWB;
extern _MEMWB shadow_MEMWB;


#endif //ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H
