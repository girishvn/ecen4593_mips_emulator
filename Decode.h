//
// Created by Girish Narayanswamy on 3/26/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_DECODE_H
#define ECEN4593_MIPS_EMULATOR_DECODE_H

#include "global_vars.h"
#include <iostream>

/***********************************************************************************************************************

Inst-type definitions and opcode bank

***********************************************************************************************************************/

#define N 0x00
#define R 0x01
#define I 0x02
#define J 0x03

//op code & funct values by type
const uint8_t ROPCode = 0x00;
//const uint8_t RFunct[15] = {0x00,0x02,0x08,0x0A,0x0B,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2A,0x2B}; //15 R TYPES
const uint8_t IOPCode[20] = {0x01,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D, 0x0E, 0x0F, 0x20, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B};
const uint8_t JOPCode[2] = {0x02, 0x03}; //2 J TYPES

/***********************************************************************************************************************

FUNCTIONS

***********************************************************************************************************************/

//function declarations
void instType(uint32_t machineCode);
void instRDecode(uint32_t machineCode);
void instIDecode(uint32_t machineCode);
void instJDecode(uint32_t machineCode);
void instDecode(void);


#endif //ECEN4593_MIPS_EMULATOR_DECODE_H
