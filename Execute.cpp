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
    if(IDEX.type == I || IDEX.type == J){
        if(IDEX.funct == 0x08){
            ADDI();
        }
        else if(IDEX.funct == 0x09){
            ADDIU();
        }
        else if(IDEX.funct == 0x0C){
            ANDI();
        }
        else if(IDEX.funct == 0x04){
            BEQ();
        }
        else if(IDEX.funct == 0x05){
            BNE();
        }
        else if(IDEX.funct == 0x02){
            JUMP();
        }
        else if(IDEX.funct == 0x03){
            JAL();
        }
        else if(IDEX.funct == 0x24){
            LBU();
        }
        else if(IDEX.funct == 0x25){
            LHU();
        }
        else if(IDEX.funct == 0x30){
            LW();
        }
        else if(IDEX.funct == 0x0F){
            LUI();
        }
        else if(IDEX.funct == 0x23){
            LW();
        }
        else if(IDEX.funct == 0x0D){
            ORI();
        }
        else if(IDEX.funct == 0x0A){
            SLTI();
        }
        else if(IDEX.funct == 0x0B){
            SLTIU();
        }
        else if(IDEX.funct == 0x28){
            SB();
        }
        else if(IDEX.funct == 0x38){
            SW();
        }
        else if(IDEX.funct == 0x29){
            SH();
        }
        else if(IDEX.funct == 0x2B){
            SW();
        }
        else{
            std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
        }
    }
    else if(IDEX.type == R){
        if(IDEX.funct == 0x20){
            ADD();
        }
        else if(IDEX.funct == 0x21){
            ADDI();
        }
        else if(IDEX.funct == 0x24){
            AND();
        }
        else if(IDEX.funct == 0x08){
            JR();
        }
        else if(IDEX.funct == 0x27){
            NOR();
        }
        else if(IDEX.funct == 0x25){
            OR();
        }
        else if(IDEX.funct == 0x2A){
            SLT();
        }
        else if(IDEX.funct == 0x2B){
            SLTU();
        }
        else if(IDEX.funct == 0x02){
            SRL();
        }
        else if(IDEX.funct == 0x22){
            SUB();
        }
        else if(IDEX.funct == 0x23){
            SUBU();
        }
        else{
            std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
        }
    }
    else{
        std::cout<<"invalid opcode or input / undocumented instruction"<<std::endl;

    }
}