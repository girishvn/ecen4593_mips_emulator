//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "global_vars.h"

void AND(){
    rd = rs & rt;
    programCount++;
}

void ANDI(){
    rt = rs & imm;
    programCount++;
}

void OR(){
    rd = rs | rt;
    programCount++;
}

void ORI(){
    rt = rs | imm;
    programCount++;
}

void XOR(){
    rd = rs ^ rt;
    programCount++;
}

void XORI(){
    rt = rs ^ imm;
    programCount++;
}

void BEQ(){
    if(rs = rt){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BGEZ(){
    if(rs >= 0){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BGEZAL(){
    if(rs >= 0){
        ra = programCount;
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BGTZ(){
    if(rs > 0){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BLEZ(){
    if(rs <= 0){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BLTZ(){
    if(rs < 0){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void BLTZAL(){
    if(rs < 0){
        programCount += imm;
    }
    else{
        programCount++;
    }
}
void BNE(){
    if(rs != rt){
        programCount += imm;
    }
    else{
        programCount++;
    }
}

void LB(){

}
void LUI();
void LW();
void SB();
void SW();

void NOOP(){
    programCount++;
}

void SLL(){
    rd = rt<<shamt;
    programCount++;
}

void SLLV(){
    rd = rt<<rs;
    programCount++;
}

void SLT(){
    if(rs < rt){
        rd = 1;
    }
    programCount++;
}

void SLTI(){

    if(rs < imm){
        rt = 1;
    }
    else{
        rt = 0;
    }
    programCount++;
}

void SLTIU(){
    if(rs < imm){
        rt = 1;
    }
    else{
        rt = 0;
    }
    programCount++;
}

void SLTU(){
    if(rs < rt){
        rd = 1;
    }
    else{
        rt = 0;
    }
    programCount++;
}

void SRA(){
    rd = rt>>shamt;
    programCount++;
}

void SRL(){
    rd = rt>>shamt;
    programCount++;
}

void SRLV(){
    rd = rt>>rs;
    programCount++;
}