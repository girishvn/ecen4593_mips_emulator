//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"

void ADD(){

}

void ADDI(){

}

void ADDIU(){

}

void ADDU(){

}

void SUB(){

}

void SUBU(){

}

void AND(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rs] & reg[IDEX.rt];
    pc++;
}

void ANDI(){
    reg[shadow_EXMEM.rt] = reg[IDEX.rs] & reg[IDEX.immediate];
    pc++;
}

void OR(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rs] | reg[IDEX.rt];
    pc++;
}

void ORI(){
    reg[shadow_EXMEM.rt] = reg[IDEX.rs] | reg[IDEX.immediate];
    pc++;
}

void XOR(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rs] ^ reg[IDEX.rt];
    pc++;
}

void XORI(){
    reg[shadow_EXMEM.rt] = reg[IDEX.rs] ^ reg[IDEX.immediate];
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
    reg[shadow_EXMEM.rt] = Memory[reg[IDEX.rs] + IDEX.immediate] >> 28;
    pc++;
}

void LUI();

void LW(){
    reg[shadow_EXMEM.rt] = Memory[reg[IDEX.rs] + IDEX.immediate];
    pc++;

}

void SB(){
    Memory[reg[IDEX.rs] + IDEX.immediate] =  (0xFF & reg[shadow_EXMEM.rt]) >> 28;
    pc++;
}

void SW(){
    Memory[reg[IDEX.rs] + IDEX.immediate] =  (0xFF & reg[shadow_EXMEM.rt]);
    pc++;
}

void NOOP(){
    pc++;
}

void SLL(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rt]<<IDEX.shamt;
    pc++;
}

void SLLV(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rt]<<reg[IDEX.rs];
    pc++;
}

void SLT(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        reg[shadow_EXMEM.rd] = 1;
    }
    pc++;
}

void SLTI(){
    if(reg[IDEX.rs] < IDEX.immediate){
        reg[shadow_EXMEM.rt] = 1;
    }
    else{
        reg[shadow_EXMEM.rt] = 0;
    }
    pc++;
}

void SLTIU(){
    if(reg[IDEX.rs] < IDEX.immediate){
        reg[shadow_EXMEM.rt] = 1;
    }
    else{
        reg[shadow_EXMEM.rt] = 0;
    }
    pc++;
}

void SLTU(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        reg[shadow_EXMEM.rd] = 1;
    }
    else{
        reg[shadow_EXMEM.rt] = 0;
    }
    pc++;
}

void SRA(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rt]>>IDEX.shamt;
    pc++;
}

void SRL(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rt]>>IDEX.shamt;
    pc++;
}

void SRLV(){
    reg[shadow_EXMEM.rd] = reg[IDEX.rt]>>reg[IDEX.rs];
    pc++;
}