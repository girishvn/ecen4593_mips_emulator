//
// Created by Girish Narayanswamy on 3/26/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_DECODE_H
#define ECEN4593_MIPS_EMULATOR_DECODE_H

#include "_instruction.h"

int instType(uint32_t machineCode, instruction *inst);
void instRDecode(uint32_t machineCode, instruction *inst);
void instIDecode(uint32_t machineCode, instruction *inst);
void instJDecode(uint32_t machineCode, instruction *inst);
void instDecode(uint32_t machineCode, instruction *inst);


#endif //ECEN4593_MIPS_EMULATOR_DECODE_H
