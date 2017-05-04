//
// Created by Karros Huang on 4/18/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_EXECUTE_H
#define ECEN4593_MIPS_EMULATOR_EXECUTE_H

#include "global_vars.h"
#include "Decode.h"
#include <iostream>

//39 total instructions needed (including seb)

/***********************************************************************************************************************

INSTRUCTION FUNCTIONS

***********************************************************************************************************************/

void ADD(void); //funct: 0x20
void ADDI(void); //op: 0x08
void ADDIU(void); //op: 0x09
void ADDU(void); //funct: 0x21
void SUB(void); //funct: 0x22
void SUBU(void); //funct: 0x23

void AND(void); //funct: 0x24
void ANDI(void); //op: 0x0C
void OR(void); //funct: 0x25
void ORI(void); //op: 0x0D
void XOR(void); //funct: 0x26
void XORI(void); //op: 0X0E
void NOR(void); //funct: 0x27

void BEQ(void); //op: 0x04
void BGTZ(void); //op: 0x07
void BLEZ(void); //op: 0x06
void BLTZ(void); //op: 0x01
void BNE(void); //op: 0x05
void JUMP(void); //op: 0x02
void JAL(void); //op: 0x03
void JR(void); //funct: 0x08

void LB(void); //op: 0x20
void LBU(void); //op: 0x24
void LUI(void); //op: 0x0F
void LW(void); //op: 0x23
void LHU(void); //op: 0x25
void SB(void); //op: 0x28
void SW(void); //op: 0x2B
void SH(void); //op: 0x29

void SLL(void); //funct: 0x00
void SLT(void); //funct: 0x2A
void SLTI(void); //op: 0x0A
void SLTIU(void); //op: 0x0B
void SLTU(void); //funct: 0x2B
void SRL(void); //funct: 0x02

void MOVN(void); //funct: 0x0B
void MOVZ(void); //funct: 0x0A

//OTHERS
int32_t zeroExt(int16_t imm); //zero extend function (called from other instructions)
void NOP(void); //inst: 0x00000000
void SEB(void); //opcode: 0x1F

/***********************************************************************************************************************

CALLABLE FUNCTIONS

***********************************************************************************************************************/

void instExecute(void);


#endif //ECEN4593_MIPS_EMULATOR_EXECUTE_H