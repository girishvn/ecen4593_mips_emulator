//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"

void ADD(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(reg[IDEX.rt])));
    pc++;
}

void ADDI(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(IDEX.immediate)));
    pc++;
}

void ADDIU(){
    shadow_EXMEM.rv = reg[IDEX.rs] + IDEX.immediate;
    pc++;
}

void ADDU(){
    shadow_EXMEM.rv = reg[IDEX.rs] + reg[IDEX.rt];
    pc++;
}

void SUB(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) - int32_t(reg[IDEX.rt])));
    pc++;
}

void SUBU(){
    shadow_EXMEM.rv = reg[IDEX.rs] - reg[IDEX.rt];
    pc++;
}

void AND(){
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.rt];
    pc++;
}

void ANDI(){
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.immediate];
    pc++;
}

void OR(){
    shadow_EXMEM.rv = reg[IDEX.rs] | reg[IDEX.rt];
    pc++;
}

void ORI(){
    shadow_EXMEM.rv = reg[IDEX.rs] | reg[IDEX.immediate];
    pc++;
}

void XOR(){
    shadow_EXMEM.rv = reg[IDEX.rs] ^ reg[IDEX.rt];
    pc++;
}

void XORI(){
    shadow_EXMEM.rv = reg[IDEX.rs] ^ reg[IDEX.immediate];
    pc++;
}

void BEQ(){
    if(reg[IDEX.rs] == reg[IDEX.rt]){
        pc += reg[IDEX.immediate];
    }
    else{
        pc++;
    }
}

void BGEZ(){
    if(reg[IDEX.rs] >= 0){
        pc += reg[IDEX.immediate];
    }
    else{
        pc++;
    }
}

void BGEZAL(){
    if(reg[IDEX.rs] >= 0){
        reg[IDEX.ra] = pc;
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BGTZ(){
    if(reg[IDEX.rs] > 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLEZ(){
    if(reg[IDEX.rs] <= 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLTZ(){
    if(reg[IDEX.rs] < 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLTZAL(){
    if(reg[IDEX.rs] < 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BNE(){
    if(reg[IDEX.rs] != reg[IDEX.rt]){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void LB(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate; //loading memory address into rv
    pc++;
}

void LUI(){
    shadow_EXMEM.address = IDEX.immediate << 16; //loading upper half of immediate value into rv
    pc++;
}

void LW(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate; //loading memory address into rv
    pc++;
}

void SB(){
    shadow_EXMEM.rv =  (0xFF & shadow_EXMEM.rv) >> 24; //
    shadow_EXMEM.address = IDEX.rs + IDEX.immediate;
    pc++;
}

void SW(){
    shadow_EXMEM.rv =  (0xFF & shadow_EXMEM.rv);
    shadow_EXMEM.address = IDEX.rs + IDEX.immediate;
    pc++;
}

void SLL(){
    shadow_EXMEM.rv = reg[IDEX.rt]<<IDEX.shamt;
    pc++;
}

void SLLV(){
    shadow_EXMEM.rv = reg[IDEX.rt]<<reg[IDEX.rs];
    pc++;
}

void SLT(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        shadow_EXMEM.rv = 1;
    }
    pc++;
}

void SLTI(){
    if(reg[IDEX.rs] < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    pc++;
}

void SLTIU(){
    if(reg[IDEX.rs] < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    pc++;
}

void SLTU(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    pc++;
}

void SRA(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    pc++;
}

void SRL(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    pc++;
}

void SRLV(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>reg[IDEX.rs];
    pc++;
}