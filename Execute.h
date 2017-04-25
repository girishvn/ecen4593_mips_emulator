//
// Created by Karros Huang on 4/18/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_EXECUTE_H
#define ECEN4593_MIPS_EMULATOR_EXECUTE_H

#include "global_vars.h"

void ADD(void);
void ADDI(void);
void ADDIU(void);
void ADDU(void);
void SUB(void);
void SUBU(void);

void AND(void);
void ANDI(void);
void OR(void);
void ORI(void);
void XOR(void);
void XORI(void);
void NOR(void);

void BEQ(void);
void BGEZ(void);
void BGEZAL(void);
void BGTZ(void);
void BLEZ(void);
void BLTZ(void);
void BLTZAL(void);
void BNE(void);
void JUMP(void);
void JAL(void);
void JR(void);

void LBU(void);
void LUI(void);
void LW(void);
void LHU(void);
void SB(void);
void SW(void);
void SH(void);

void NOOP(void);

void SLL(void);
void SLLV(void);
void SLT(void);
void SLTI(void);
void SLTIU(void);
void SLTU(void);
void SRA(void);
void SRL(void);
void SRLV(void);

void instExecute(void);


#endif //ECEN4593_MIPS_EMULATOR_EXECUTE_H
