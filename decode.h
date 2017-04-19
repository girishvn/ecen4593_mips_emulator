//
// Created by Girish Narayanswamy on 3/26/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_DECODE_H
#define ECEN4593_MIPS_EMULATOR_DECODE_H

#include <iostream>
#include "global_vars.h"

#define R 0x01
#define I 0x02
#define J 0x03

//op code values by type
const uint8_t ROPCode = 0x00;
const uint8_t IOPCode[] = {0x04, 0x05, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B, 0x30, 0x38};
const uint8_t JOPCode[] = {0x02, 0x03};

//function declarations
void instType(uint32_t machineCode);
void instRDecode(uint32_t machineCode);
void instIDecode(uint32_t machineCode);
void instJDecode(uint32_t machineCode);
void instDecode(uint32_t machineCode);


#endif //ECEN4593_MIPS_EMULATOR_DECODE_H
