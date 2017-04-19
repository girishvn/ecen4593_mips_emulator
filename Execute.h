//
// Created by Karros Huang on 4/18/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_EXECUTE_H
#define ECEN4593_MIPS_EMULATOR_EXECUTE_H

void ADD();
void ADDI();
void ADDIU();
void ADDU();
void SUB();
void SUBU();

void AND();
void ANDI();
void OR();
void ORI();
void XOR();
void XORI();

void BEQ();
void BGEZ();
void BGEZAL();
void BGTZ();
void BLEZ();
void BLTZ();
void BLTZAL();
void BNE();

void LB();
void LUI();
void LW();
void SB();
void SW();

void NOOP();

void SLL();
void SLLV();
void SLT();
void SLTI();
void SLTIU();
void SLTU();
void SRA();
void SRL();
void SRLV();




#endif //ECEN4593_MIPS_EMULATOR_EXECUTE_H
