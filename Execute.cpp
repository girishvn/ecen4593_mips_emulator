//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"
#include "Decode.h"

void ADD(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(reg[IDEX.rt])));
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    pc++;
}

void ADDI(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(IDEX.immediate)));
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDIU(){
    shadow_EXMEM.rv = reg[IDEX.rs] + IDEX.immediate;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDU(){
    shadow_EXMEM.rv = reg[IDEX.rs] + reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SUB(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) - int32_t(reg[IDEX.rt])));
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SUBU(){
    shadow_EXMEM.rv = reg[IDEX.rs] - reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void AND(){
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ANDI(){
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.immediate];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void OR(){
    shadow_EXMEM.rv = reg[IDEX.rs] | reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ORI(){
    shadow_EXMEM.rv = reg[IDEX.rs] | reg[IDEX.immediate];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void XOR(){
    shadow_EXMEM.rv = reg[IDEX.rs] ^ reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void XORI(){
    shadow_EXMEM.rv = reg[IDEX.rs] ^ reg[IDEX.immediate];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void NOR(){
    shadow_EXMEM.rv = ~(reg[IDEX.rs] | reg[IDEX.rt]);
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

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
    if(int32_t(reg[IDEX.rs]) >= 0){
        pc += reg[IDEX.immediate];
    }
    else{
        pc++;
    }
}

void BGEZAL(){
    if(int32_t(reg[IDEX.rs]) >= 0){
        reg[shadow_EXMEM.ra] = pc++;
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BGTZ(){
    if(int32_t(reg[IDEX.rs]) > 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLEZ(){
    if(int32_t(reg[IDEX.rs]) <= 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLTZ(){
    if(int32_t(reg[IDEX.rs]) < 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
}

void BLTZAL(){
    if(int32_t(reg[IDEX.rs]) < 0){
        reg[shadow_EXMEM.ra] = pc++;
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

void JUMP(){
    pc = (pc & 0xf0000000) | (IDEX.address << 2);
}

void JAL(){
    reg[shadow_EXMEM.ra] = pc++;
    pc = (pc & 0xf0000000) | (IDEX.address << 2);
}

void JR(){
    pc = reg[IDEX.rs];
}

void LBU(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate; //loading memory address into rv
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    pc++;
}


void LUI(){
    shadow_EXMEM.rv = IDEX.immediate << 16; //loading upper half of immediate value into rv
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    pc++;
}

void LW(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate; //loading memory address into rv
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    pc++;
}

void LHU(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate; //loading memory address into rv
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SB(){
    shadow_EXMEM.rv =  (0xFF & reg[shadow_EXMEM.rt]) >> 24; //
    shadow_EXMEM.address = IDEX.rs + IDEX.immediate;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SW(){
    shadow_EXMEM.rv =  (0xFF & reg[shadow_EXMEM.rt]);
    shadow_EXMEM.address = IDEX.rs + IDEX.immediate;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SH(){
    shadow_EXMEM.rv =  (0xFF & reg[shadow_EXMEM.rt]) >> 16;
    shadow_EXMEM.address = IDEX.rs + IDEX.immediate;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SLL(){
    shadow_EXMEM.rv = reg[IDEX.rt]<<IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SLLV(){
    shadow_EXMEM.rv = reg[IDEX.rt]<<reg[IDEX.rs];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SLT(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        shadow_EXMEM.rv = 1;
    }
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SLTI(){
    if(reg[IDEX.rs] < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SLTIU(){
    if(reg[IDEX.rs] < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SLTU(){
    if(reg[IDEX.rs] < reg[IDEX.rt]){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SRA(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SRL(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SRLV(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>reg[IDEX.rs];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void instExecute() {
    switch (IDEX.type) {
        case I or J: {
            switch (IDEX.funct) {
                case 0x08: {
                    ADDI();
                }
                case 0x09: {
                    ADDIU();
                }
                case 0x0C: {
                    ANDI();
                }
                case 0x04: {
                    BEQ();
                }
                case 0x05: {
                    BNE();
                }
                case 0x02: {
                    JUMP();
                }
                case 0x03: {
                    JAL();
                }
                case 0x24: {
                    LBU();
                }
                case 0x25: {
                    LHU();
                }
                case 0x30: {
                    LW();
                }
                case 0x0F: {
                    LUI();
                }
                case 0x23: {
                    LW();
                }
                case 0x0D: {
                    ORI();
                }
                case 0x0A: {
                    SLTI();
                }
                case 0x0B: {
                    SLTIU();
                }
                case 0x28: {
                    SB();
                }
                case 0x38: {
                    SW();
                }
                case 0x29: {
                    SH();
                }
                case 0x2B: {
                    SW();
                }
                default: {
                    std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
                }
            }
        }
        case R: {
            switch (IDEX.funct) {
                case 0x20: {
                    ADD();
                }
                case 0x21: {
                    ADDI();
                }
                case 0x24: {
                    AND();
                }
                case 0x08: {
                    JR();
                }
                case 0x27: {
                    NOR();
                }
                case 0x25: {
                    OR();
                }
                case 0x2A: {
                    SLT();
                }
                case 0x2B: {
                    SLTU();
                }
                case 0x02: {
                    SRL();
                }
                case 0x22: {
                    SUB();
                }
                case 0x23: {
                    SUBU();
                }
                default: {
                    std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
                }
            }
        }
        default: {
            std::cout<<"invalid opcode or input / undocumented instruction"<<std::endl;
        }
    }
}