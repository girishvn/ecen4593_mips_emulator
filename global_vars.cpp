//
// Created by Girish Narayanswamy on 4/19/17.
//

#include "global_vars.h"

//Global Variables:

uint32_t reg[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //32-register system
uint32_t pc = 0; //program counter

//Intermediate Registers

_IFID IFID;
_IFID shadow_IFID;

_IDEX IDEX;
_IDEX shadow_IDEX;

_EXMEM EXMEM;
_EXMEM shadow_EXMEM;

_MEMWB MEMWB;
_MEMWB shadow_MEMWB;