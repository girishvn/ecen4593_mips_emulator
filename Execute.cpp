//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"


/***********************************************************************************************************************

ARITHMETIC FUNCTIONS

***********************************************************************************************************************/

void ADD(){ //R
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(reg[IDEX.rt])));
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDI(){ //I
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(IDEX.immediate)));
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDIU(){ //I
    shadow_EXMEM.rv = reg[IDEX.rs] + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDU(){ //R
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

/***********************************************************************************************************************

LOGICAL FUNCTIONS

***********************************************************************************************************************/

void AND(){ //R
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ANDI(){ //I
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.immediate];
    shadow_EXMEM.rt = IDEX.rt;
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
    shadow_EXMEM.rt = IDEX.rt;
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
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void NOR(){
    shadow_EXMEM.rv = ~(reg[IDEX.rs] | reg[IDEX.rt]);
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

/***********************************************************************************************************************

BRANCH FUNCTIONS

***********************************************************************************************************************/

void BEQ(){
    if(reg[IDEX.rs] == reg[IDEX.rt]){
        pc += reg[IDEX.immediate];
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BGTZ(){
    if(int32_t(reg[IDEX.rs]) > 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BLEZ(){
    if(int32_t(reg[IDEX.rs]) <= 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BLTZ(){
    if(int32_t(reg[IDEX.rs]) < 0){
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BNE(){
    if(reg[IDEX.rs] != reg[IDEX.rt]){
        pc += int(IDEX.immediate) + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

/***********************************************************************************************************************

JUMP FUNCTIONS

***********************************************************************************************************************/

void JUMP(){
    pc = (pc & 0xf0000000) | (IDEX.address << 2);
    shadow_EXMEM.type = IDEX.type;
}

void JAL(){
    shadow_EXMEM.rv = pc + 1;
    shadow_EXMEM.ra = EXMEM.ra;
    pc = (pc & 0xf0000000) | (IDEX.address << 2);
    shadow_EXMEM.opcode = IDEX.opcode; //After Execute stage, this function now acts as a R type
    shadow_EXMEM.type = IDEX.type;
}

void JR(){
    pc = reg[IDEX.rs];
    shadow_EXMEM.type = IDEX.type;
}

/***********************************************************************************************************************

LOAD FUNCTIONS

***********************************************************************************************************************/
//LOAD BYTE
void LB(){
    return;
}

//LOAD BYTE UNSIGNED
void LBU(){

    //LOCAL VARIABLES
    uint32_t memVal;
    uint32_t regVal;
    uint8_t byteIdx; //byte index with word
    uint32_t maskMem;
    uint32_t maskReg;

    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //loading memory address into rv

    regVal = reg[IDEX.rt];
    memVal = memory[shadow_EXMEM.address];
    byteIdx = uint8_t(IDEX.immediate%4);

    switch (byteIdx) {
        case 0: { //1th Byte
            maskMem = 0x000000ff;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            regVal = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0x0000ff00;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 8;

            regVal = memVal | regVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0x00ff0000;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 16;

            regVal = memVal | regVal;

            break;

        }

        case 3: { //4th Byte
            maskMem = 0xff000000;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 24;

            regVal = memVal | regVal;

            break;

        }

        default: {
            std::cout<<"unusable index value in LBU"<<std::endl;
            return;
        }
    }

    shadow_EXMEM.rv = regVal;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

//LOAD UNSIGNED IMMEDIATE
void LUI(){

    uint32_t regVal = reg[IDEX.rt] & 0x0000ffff;
    regVal = regVal | (IDEX.immediate << 16);

    shadow_EXMEM.rv = regVal; //loading upper half of immediate value into rv

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    pc++;
}

//LOAD WORD
void LW(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //loading memory address into rv
    shadow_EXMEM.rv = memory[shadow_EXMEM.address];
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    pc++;
}

//LOAD UNSIGNED HALF-WORD
void LHU(){

    //LOCAL VARIABLES
    uint32_t memVal;
    uint32_t regVal;
    uint8_t byteIdx; //byte index with word
    uint32_t maskMem;
    uint32_t maskReg;

    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //loading memory address into rv
    std::cout<<"address "<<+shadow_EXMEM.address<<std::endl;

    regVal = reg[IDEX.rt];
    memVal = memory[shadow_EXMEM.address];

    std::cout<<"reg val "<<+reg[IDEX.rt]<<" mem val "<<+memVal<<std::endl;

    byteIdx = uint8_t(IDEX.immediate%4);

    switch (byteIdx) {
        case 0: { //1th Byte
            maskMem = 0x0000ffff;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            regVal = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0x00ffff00;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 8;

            regVal = memVal | regVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0xffff0000;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 16;

            regVal = memVal | regVal;

            break;

        }

        default: {
            std::cout<<"unusable index value in LHU"<<std::endl;
            return;
        }
    }

    shadow_EXMEM.rv = regVal;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

/***********************************************************************************************************************

STORE FUNCTIONS

***********************************************************************************************************************/

void SB(){
    //LOCAL VARIABLES
    uint32_t memVal;
    uint32_t regVal;
    uint8_t byteIdx; //byte index with word
    uint32_t maskMem;
    uint32_t maskReg;

    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //calculate address with offset

    memVal = memory[shadow_EXMEM.address];
    regVal = reg[IDEX.rt];
    byteIdx = uint8_t(IDEX.immediate%4);

    switch (byteIdx) {
        case 0: { //1th Byte
            maskMem = 0xffffff00;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            memVal = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0xffff00ff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            regVal = regVal << 8;

            memVal = memVal | regVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0xff00ffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            regVal = regVal << 16;

            memVal = memVal | regVal;

            break;

        }

        case 3: { //4th Byte
            maskMem = 0x00ffffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            regVal = regVal << 24;

            memVal = memVal | regVal;

            break;

        }

        default: {
            std::cout<<"unusable index value in SH"<<std::endl;
            return;
        }
    }

    shadow_EXMEM.rv = memVal;
    shadow_EXMEM.rs = IDEX.rs;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.immediate = IDEX.immediate;

    pc++;
}

//STORE WORD
void SW(){
    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //calculate address with offset

    if(IDEX.immediate%4 != 0){
        std::cout<<"SW immediate offset crosses memory words: "<<IDEX.funct<<std::endl;
        return;
    }

    shadow_EXMEM.rv =  reg[IDEX.rt]; //stores full word
    shadow_EXMEM.rs = IDEX.rs;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.immediate = IDEX.immediate;

    pc++;

    return;
}

//STORE HALF WORD
void SH(){

    //LOCAL VARIABLES
    uint32_t memVal;
    uint32_t regVal;
    uint8_t byteIdx; //byte index with word
    uint32_t maskMem;
    uint32_t maskReg;

    shadow_EXMEM.address = reg[IDEX.rs] + IDEX.immediate/4; //calculate address with offset

    memVal = memory[shadow_EXMEM.address];
    regVal = reg[IDEX.rt];
    byteIdx = uint8_t(IDEX.immediate%4);

    switch (byteIdx) {
        case 0: { //1th Byte
            maskMem = 0xffff0000;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            memVal = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0xff0000ff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            regVal = regVal << 8;

            memVal = memVal | regVal;

            break;
        }

        case 2: { //3th Byte
            maskMem = 0x0000ffff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            regVal = regVal << 16;

            memVal = memVal | regVal;

            break;
        }

        default: { //4th Byte
            std::cout<<"unusable index value in SH"<<std::endl;
            return;
        }
    }

    shadow_EXMEM.rv =  memVal;
    shadow_EXMEM.rs = IDEX.rs;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.immediate = IDEX.immediate;

    pc++;

    return;
}

/***********************************************************************************************************************

OTHER THINGS THAT DO NOT BELONG

***********************************************************************************************************************/

void SLL(){
    shadow_EXMEM.rv = reg[IDEX.rt]<<IDEX.shamt;
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

void SRL(){
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void MOVN(){
    if(reg[IDEX.rt] != 0x0000){
        shadow_EXMEM.rv = reg[IDEX.rs];
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.type = J; //failed mov condition and thus must not operate in memory or writeback stages
    }

    pc++;
}

void MOVZ(){
    if(reg[IDEX.rt] == 0x0000){
        shadow_EXMEM.rv = reg[IDEX.rs];
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.type = J; //failed mov condition and thus must not operate in memory or writeback stages
    }

    pc++;
}

void NOP(){
    shadow_EXMEM.nop = true;
    pc++;
}

/***********************************************************************************************************************

UNNEEDED FUNCTIONS

***********************************************************************************************************************/

void BGEZ(){ //uneeded
    if(int32_t(reg[IDEX.rs]) >= 0){
        pc += reg[IDEX.immediate];
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BGEZAL(){ //uneeded
    if(int32_t(reg[IDEX.rs]) >= 0){
        reg[shadow_EXMEM.ra] = pc++;
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BLTZAL(){ //uneeded
    if(int32_t(reg[IDEX.rs]) < 0){
        reg[shadow_EXMEM.ra] = pc++;
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void SLLV(){ //uneeded
    shadow_EXMEM.rv = reg[IDEX.rt]<<reg[IDEX.rs];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SRA(){ //uneeded
    shadow_EXMEM.rv = reg[IDEX.rt]>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void SRLV(){ //uneeded
    shadow_EXMEM.rv = reg[IDEX.rt]>>reg[IDEX.rs];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}


/***********************************************************************************************************************

 FUNCTION NAME: instExecute

 DESCRIPTION: Executes instruction

 INPUTS: void (fills from IDEX register)

 OUTPUTS: void (fills shadow_EXMEM Reg with proper instruction information)

***********************************************************************************************************************/

void instExecute() {

    //nop instruction detection
    shadow_EXMEM.nop = false; //nop by defualt is false

    //I OR J TYPE
    if(IDEX.type == I || IDEX.type == J){

        //J TYPES
        if(IDEX.opcode == 0x02){ //J
            JUMP();
        }
        else if(IDEX.opcode == 0x03){ //JAL
            JAL();
        }

        //I TYPES
        else if(IDEX.opcode == 0x01){ //BLTZ
            BLTZ();
        }
        else if(IDEX.opcode == 0x04){ //BEQ
            BEQ();
        }
        else if(IDEX.opcode == 0x05){ //BNE
            BNE();
        }
        else if(IDEX.opcode == 0x06){ //BLEZ
            BLEZ();
        }
        else if(IDEX.opcode == 0x07){ //BGTZ
            BGTZ();
        }
        else if(IDEX.opcode == 0x08){ //ADDI
            ADDI();
        }
        else if(IDEX.opcode == 0x09){ //ADDIU
            ADDIU();
        }
        else if(IDEX.opcode == 0x0A){ //SLTI
            SLTI();
        }
        else if(IDEX.opcode == 0x0B){ //SLTIU
            SLTIU();
        }
        else if(IDEX.opcode == 0x0C){ //ANDI
            ANDI();
        }
        else if(IDEX.opcode == 0x0D){ //ORI
            ORI();
        }
        else if(IDEX.opcode == 0x0E){ //XORI
            XORI();
        }
        else if(IDEX.opcode == 0x0F){ //LUI
            LUI();
        }
        else if(IDEX.opcode == 0x20){ //LUI
            LB(); //needs to be written
        }
        else if(IDEX.opcode == 0x23){ //LW
            LW();
        }
        else if(IDEX.opcode == 0x24){ //LBU
            LBU();
        }
        else if(IDEX.opcode == 0x25){ //LHU
            LHU();
        }
        else if(IDEX.opcode == 0x28){ //SB
            SB();
        }
        else if(IDEX.opcode == 0x29){ //SH
            SH();
        }
        else if(IDEX.opcode == 0x2B){ //SW
            SW();
        }
        else{
            std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
        }
    }

    //R TYPE
    else if(IDEX.type == R){
        if(IDEX.mc == 0x00000000){ //NOP
            NOP();
        }
        else if(IDEX.funct == 0x00){ //SLL
            SLL();
        }
        else if(IDEX.funct == 0x02){ //SRL
            SRL();
        }
        else if(IDEX.funct == 0x08){ //JR
            JR();
        }
        else if(IDEX.funct == 0x0A) { //MOVZ
            MOVZ();
        }
        else if(IDEX.funct == 0x0B) { //MOVN
            MOVN();
        }
        else if(IDEX.funct == 0x20){ //ADD
            ADD();
        }
        else if(IDEX.funct == 0x21){ //ADDU
            ADDU();
        }
        else if(IDEX.funct == 0x22){ //SUB
            SUB();
        }
        else if(IDEX.funct == 0x23){ //SUBU
            SUBU();
        }
        else if(IDEX.funct == 0x24){ //AND
            AND();
        }
        else if(IDEX.funct == 0x25){ //OR
            OR();
        }
        else if(IDEX.funct == 0x26){ //XOR
            XOR();
        }
        else if(IDEX.funct == 0x27){ //NOR
            NOR();
        }
        else if(IDEX.funct == 0x2A){ //SLT
            SLT();
        }
        else if(IDEX.funct == 0x2B){ //SLTU
            SLTU();
        }
        else{
            std::cout<<"Invalid Function: "<<IDEX.funct<<std::endl;
        }
    }

    //DEFAULT CASE (MEETS NO TYPES)
    else{
        std::cout<<"invalid opcode or input / undocumented instruction"<<std::endl;

    }
}