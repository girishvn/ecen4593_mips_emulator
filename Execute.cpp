//
// Created by Karros Huang on 4/18/17.
//Take care of signed and unsigned

#include "Execute.h"


/***********************************************************************************************************************

ARITHMETIC FUNCTIONS

***********************************************************************************************************************/

void ADD(){ //good
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(reg[IDEX.rt])));
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDI(){
    shadow_EXMEM.rv = uint32_t((int32_t(reg[IDEX.rs]) + int32_t(IDEX.immediate)));
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ADDIU(){
    shadow_EXMEM.rv = reg[IDEX.rs] + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
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

/***********************************************************************************************************************

LOGICAL FUNCTIONS

***********************************************************************************************************************/

void AND(){
    shadow_EXMEM.rv = reg[IDEX.rs] & reg[IDEX.rt];
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;

    pc++;
}

void ANDI(){
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
void LBU() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t(IDEX.immediate % 4);

    //shadow_EXMEM.rs = IDEX.rs; //dont think weneed this since we have rsVal
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    //shadow_EXMEM.immediate = IDEX.immediate; //dont think we need this since we calculate address

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
    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate/4;
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
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate / 4;
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
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate / 4;
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
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate/4;
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
    shadow_EXMEM.address = IDEX.rsVal + IDEX.immediate / 4;
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