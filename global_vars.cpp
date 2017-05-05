//
// Created by Girish Narayanswamy on 4/19/17.
//

#include "global_vars.h"

//Global Variables:

int32_t reg[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //32-register system
int32_t pc = 0; //program counter
uint32_t ClockCycles = 0; //Cycle Counter
uint32_t InstructionCount = 0; //Instruction count
int32_t BranchPC = -1; //Calculated branch address
bool BranchFlag = false; //Set true if a branch instruction is set
//Intermediate Registers (declarations)

_IFID IFID; //intermediate fetch/decode register
_IFID shadow_IFID; //intermediate shadow fetch/decode register

_IDEX IDEX; //intermediate decode/execute register
_IDEX shadow_IDEX; //intermediate shadow decode/execute register

_EXMEM EXMEM; //intermediate execute/memory register
_EXMEM shadow_EXMEM; //intermediate shadow execute/memory register

_MEMWB MEMWB; //intermediate memory/write back register
_MEMWB shadow_MEMWB; //intermediate shadow memory/write back register