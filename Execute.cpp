//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"

/***********************************************************************************************************************

Sign/Zero Extend FUNCTIONS

***********************************************************************************************************************/

int32_t zeroExt(int16_t imm) { //good
    int32_t zeroExtImm = int32_t(imm);
    int32_t zeroMask = 0x0000FFFF;

    zeroExtImm = zeroMask & zeroExtImm;

    return zeroExtImm;
}

/***********************************************************************************************************************

ARITHMETIC FUNCTIONS

***********************************************************************************************************************/

void ADD(){ //good
    shadow_EXMEM.rv = IDEX.rsVal + IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void ADDI(){ //good
    shadow_EXMEM.rv = IDEX.rsVal + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void ADDIU(){ //good
    shadow_EXMEM.rv = IDEX.rsVal + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void ADDU(){ //good
    shadow_EXMEM.rv = IDEX.rsVal + IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SUB(){ //good
    shadow_EXMEM.rv = IDEX.rsVal - IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SUBU(){ //good
    shadow_EXMEM.rv = IDEX.rsVal - IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

/***********************************************************************************************************************

LOGICAL FUNCTIONS

***********************************************************************************************************************/

void AND(){ //good
    shadow_EXMEM.rv = IDEX.rsVal & IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void ANDI(){ //good
    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal & imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void OR(){ //good
    shadow_EXMEM.rv = IDEX.rsVal | IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void ORI(){ //good
    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal | imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void XOR(){ //good
    shadow_EXMEM.rv = IDEX.rsVal ^ IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void XORI(){ //good
    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal ^ imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void NOR(){ //good
    shadow_EXMEM.rv = ~(IDEX.rsVal | IDEX.rtVal);
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

/***********************************************************************************************************************

BRANCH FUNCTIONS

***********************************************************************************************************************/
//NOTE: IF PC IS INCREMENTED IN FETCH INSTEAD OF EXECUTE: GET RID OF +1 INCREMENTATION OF PC IN BRANCHES AND JUMPS


void BEQ(){
    if(IDEX.rsVal == IDEX.rtVal){
        pc += IDEX.immediate + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;
}

void BGTZ(){ //same as beq
    if(IDEX.rsVal > 0){
        pc += IDEX.immediate + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;
}

void BLEZ(){ //same as beq
    if(IDEX.rsVal <= 0){
        pc += IDEX.immediate + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;
}

void BLTZ(){ //same as beq
    if(IDEX.rsVal < 0){
        pc += IDEX.immediate + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;
}

void BNE(){ //same as beq
    if(IDEX.rsVal != IDEX.rtVal){
        pc += IDEX.immediate + 1;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;
}

/***********************************************************************************************************************

JUMP FUNCTIONS

***********************************************************************************************************************/

void JUMP(){
    int32_t npc;
    npc = ((4*pc + 4) & 0xf0000000) | (IDEX.address << 2);
    pc = npc >> 2;

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
}

void JAL(){
    shadow_EXMEM.rv = (pc + 2) * 4;

    int32_t npc;
    npc = ((4*pc + 4) & 0xf0000000) | (IDEX.address << 2);
    pc = npc >> 2;

    shadow_EXMEM.opcode = IDEX.opcode; //After Execute stage, this function now acts as a R type
    shadow_EXMEM.type = IDEX.type;
}

void JR(){
    int32_t npc;
    npc = IDEX.rsVal;
    pc = npc >> 2;

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
}

/***********************************************************************************************************************

LOAD FUNCTIONS

***********************************************************************************************************************/
//LOAD BYTE
void LB(){
    return;
}

//LOAD BYTE UNSIGNED
void LBU() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate % 4);

    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}


//LOAD UPPER IMMEDIATE
void LUI(){

    int32_t regVal = IDEX.rtVal/4 & 0x0000ffff;
    regVal = regVal | (IDEX.immediate << 16);

    shadow_EXMEM.rv = regVal; //loading upper half of immediate value into rv

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    pc++;
}

//LOAD WORD
void LW(){
    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate/4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate%4);

    //If storing a word, index should always be at 0
    if(shadow_EXMEM.byteIndex != 0){
        std::cout<<"SW immediate offset crosses memory words: "<<IDEX.funct<<std::endl;
        return;
    }

    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}

//LOAD UNSIGNED HALF-WORD
void LHU() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate % 4);

    //If storing a word, index should always be at 0
    if (shadow_EXMEM.byteIndex == 4) {
        std::cout << "SW immediate offset crosses memory words: " << IDEX.funct << std::endl;
        return;
    }

    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}


/***********************************************************************************************************************

STORE FUNCTIONS

***********************************************************************************************************************/

void SB() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate % 4);

    shadow_EXMEM.rtVal = IDEX.rtVal;
    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    //shadow_EXMEM.rt = IDEX.rt; //dont think we need this since we have rtVal
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}


//STORE WORD
void SW(){
    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate/4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate%4);

    //If storing a word, index should always be at 0
    if(shadow_EXMEM.byteIndex != 0){
        std::cout<<"SW immediate offset crosses memory words: "<<IDEX.funct<<std::endl;
        return;
    }

    shadow_EXMEM.rtVal =  IDEX.rtVal;
    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    //shadow_EXMEM.rt = IDEX.rt; //dont think we need this since we have rtVal
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}

//STORE HALF WORD
void SH() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate % 4);

    //If storing a half word, index should only be at 1, 2, or 3
    if (shadow_EXMEM.byteIndex == 3) {
        std::cout << "SH immediate offset crosses memory words: " << IDEX.funct << std::endl;
        return;
    }

    shadow_EXMEM.rtVal = IDEX.rtVal;
    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    //shadow_EXMEM.rt = IDEX.rt; //dont think we need this since we have rtVal
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

    pc++;
}

/***********************************************************************************************************************

OTHER THINGS THAT DO NOT BELONG

***********************************************************************************************************************/

void SLL(){
    shadow_EXMEM.rv = IDEX.rtVal<<IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SLT(){
    if(IDEX.rsVal < IDEX.rtVal){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SLTI(){
    if(IDEX.rsVal < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SLTIU(){
    if(IDEX.rsVal < IDEX.immediate){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SLTU(){
    if(IDEX.rsVal < IDEX.rtVal){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void SRL(){
    shadow_EXMEM.rv = IDEX.rtVal>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    pc++;
}

void MOVN(){
    if(IDEX.rtVal != 0x0000){
        shadow_EXMEM.rv = reg[IDEX.rs];
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.type = J; //failed mov condition and thus must not operate in memory or writeback stages
    }

    shadow_EXMEM.opcode = IDEX.opcode;
    pc++;
}

void MOVZ(){
    if(IDEX.rtVal == 0x0000){
        shadow_EXMEM.rv = reg[IDEX.rs];
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.type = J; //failed mov condition and thus must not operate in memory or writeback stages
    }

    shadow_EXMEM.opcode = IDEX.opcode;
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
        shadow_EXMEM.rv = pc + 2;
        pc += IDEX.immediate;
    }
    else{
        pc++;
    }
    shadow_EXMEM.type = IDEX.type;
}

void BLTZAL(){ //uneeded
    if(int32_t(reg[IDEX.rs]) < 0){
        shadow_EXMEM.rv = pc + 2;
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

    if(IDEX.type == N){
        NOP();
    }

    //I OR J TYPE
    else if(IDEX.type == I || IDEX.type == J){

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
        else if(IDEX.opcode == 0x25) { //LHU
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
        if(IDEX.funct == 0x00){ //SLL
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
        std::cout<<"invalid opcode or input / undocumented instruction"<<+IDEX.opcode<<std::endl;

    }
}