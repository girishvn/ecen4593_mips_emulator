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


}

void ADDI(){

    shadow_EXMEM.rv = IDEX.rsVal + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void ADDIU(){ //good

    shadow_EXMEM.rv = IDEX.rsVal + IDEX.immediate;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void ADDU(){ //good

    shadow_EXMEM.rv = IDEX.rsVal + IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void SUB(){ //good

    shadow_EXMEM.rv = IDEX.rsVal - IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void SUBU(){ //good

    shadow_EXMEM.rv = IDEX.rsVal - IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

/***********************************************************************************************************************

LOGICAL FUNCTIONS

***********************************************************************************************************************/

void AND(){ //good

    shadow_EXMEM.rv = IDEX.rsVal & IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void ANDI(){ //good

    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal & imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void OR(){ //good

    shadow_EXMEM.rv = IDEX.rsVal | IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void ORI(){ //good

    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal | imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void XOR(){ //good

    shadow_EXMEM.rv = IDEX.rsVal ^ IDEX.rtVal;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void XORI(){ //good

    int32_t imm = zeroExt(IDEX.immediate);

    shadow_EXMEM.rv = IDEX.rsVal ^ imm;
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void NOR(){ //good

    shadow_EXMEM.rv = ~(IDEX.rsVal | IDEX.rtVal);
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

/***********************************************************************************************************************

BRANCH FUNCTIONS

***********************************************************************************************************************/
//NOTE: IF PC IS INCREMENTED IN FETCH INSTEAD OF EXECUTE: GET RID OF +1 INCREMENTATION OF PC IN BRANCHES AND JUMPS


void BEQ(){ //good

    if(IDEX.rsVal == IDEX.rtVal){
        BranchPC = pc + IDEX.immediate;
        BranchFlag = true;
    }

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;

}

void BGTZ(){ //good

    if(IDEX.rsVal > 0){
        BranchPC = pc + IDEX.immediate;
        BranchFlag = true;
    }

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;

}

void BLEZ(){ //good

    if(IDEX.rsVal <= 0){
        BranchPC = pc + IDEX.immediate;
        BranchFlag = true;
    }

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;

}

void BLTZ(){ //good

    if(IDEX.rsVal < 0){
        BranchPC = pc + IDEX.immediate;
        BranchFlag = true;
    }

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;

}

void BNE(){ //good

    if(IDEX.rsVal != IDEX.rtVal){
        BranchPC = pc + IDEX.immediate;
        BranchFlag = true;
        std::cout<<BranchPC<<std::endl;
    }

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true;

}

/***********************************************************************************************************************

JUMP FUNCTIONS

***********************************************************************************************************************/

void JUMP(){ //good

    int32_t npc;
    npc = ((4*pc) & 0xf0000000) | (IDEX.address << 2);
    BranchPC = npc >> 2;
    BranchFlag = true;

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true; //no mem-access or write back

}

void JAL(){ //good

    shadow_EXMEM.rv = (pc + 1)*4;

    int32_t npc;
    npc = ((4*pc) & 0xf0000000) | (IDEX.address << 2);
    BranchPC = npc >> 2;
    BranchFlag = true;

    shadow_EXMEM.opcode = IDEX.opcode; //After Execute stage, this function now acts as a R type
    shadow_EXMEM.type = IDEX.type;

}

void JR(){ //good

    int32_t npc;
    npc = IDEX.rsVal;
    BranchPC = npc >> 2;
    BranchFlag = true;

    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;
    shadow_EXMEM.nop = true; //no mem-access or write back

}

/***********************************************************************************************************************

LOAD FUNCTIONS

***********************************************************************************************************************/
//LOAD BYTE
void LB(){

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

//LOAD BYTE UNSIGNED
void LBU() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

//LOAD UPPER IMMEDIATE
void LUI(){

    int32_t regVal = IDEX.rtVal & 0x0000ffff;
    regVal = regVal | (int32_t((IDEX.immediate) << 16) & 0xffff0000);
    shadow_EXMEM.rv = regVal; //loading upper half of immediate value into rv

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

//LOAD WORD
void LW(){ //good

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate/4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    //If storing a word, index should always be at 0
    if(shadow_EXMEM.byteIndex != 0){
        std::cout<<"SW immediate offset crosses memory words: "<<IDEX.funct<<std::endl;
        return;
    }

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

//LOAD UNSIGNED HALF-WORD
void LHU() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    //If storing a word, index should always be at 0
    if (shadow_EXMEM.byteIndex == 4) {
        std::cout << "SW immediate offset crosses memory words: " << IDEX.funct << std::endl;
        return;
    }

    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}


/***********************************************************************************************************************

STORE FUNCTIONS

***********************************************************************************************************************/

void SB() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    shadow_EXMEM.rtVal = 0x000000ff & IDEX.rtVal; //only lowest byte stored
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}


//STORE WORD
void SW(){ //good

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate/4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    //If storing a word, index should always be at 0
    if(shadow_EXMEM.byteIndex != 0){
        std::cout<<"SW immediate offset crosses memory words: "<<+IDEX.funct<<std::endl;
        std::cout<<"address: "<<+shadow_EXMEM.address<<" byte index: "<<+shadow_EXMEM.byteIndex<<std::endl;
        return;
    }

    shadow_EXMEM.rtVal =  IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

//STORE HALF WORD
void SH() {

    //Calculating immediate address and byte index.
    shadow_EXMEM.address = IDEX.rsVal/4 + IDEX.immediate / 4;
    shadow_EXMEM.byteIndex = uint8_t((IDEX.rsVal + IDEX.immediate) % 4);

    //If storing a half word, index should only be at 1, 2, or 3
    if (shadow_EXMEM.byteIndex == 3) {
        std::cout << "SH immediate offset crosses memory words: " << IDEX.funct << std::endl;
        return;
    }

    shadow_EXMEM.rtVal = IDEX.rtVal;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

/***********************************************************************************************************************

OTHER THINGS THAT DO NOT BELONG

***********************************************************************************************************************/
void SEB(){
    int32_t regVal = reg[IDEX.rt];
    regVal = 0x000000FF & regVal;
    int32_t mask1 = 0xFFFFFF00;
    int32_t mask0 = 0x00000000;


    if((regVal >> 7) == 1){ //sign extend with 1's
        shadow_EXMEM.rv = (mask1 | regVal);
    }
    else{ //sign extend with 0's
        shadow_EXMEM.rv = (mask0 | regVal);
    }

    shadow_EXMEM.rd = IDEX.rd; //return register passed on
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

    std::cout<<"return val: "<<+shadow_EXMEM.rv<<" rtVal:"<<reg[IDEX.rt]<<std::endl;
}

void SLL(){

    shadow_EXMEM.rv = IDEX.rtVal<<IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

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

}

void SLTIU(){

    if(IDEX.rsVal < uint16_t(IDEX.immediate)){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rt = IDEX.rt;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void SLTU(){

    if(uint32_t(IDEX.rsVal) < uint16_t(IDEX.rtVal)){
        shadow_EXMEM.rv = 1;
    }
    else{
        shadow_EXMEM.rv = 0;
    }
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void SRL(){

    shadow_EXMEM.rv = IDEX.rtVal>>IDEX.shamt;
    shadow_EXMEM.rd = IDEX.rd;
    shadow_EXMEM.type = IDEX.type;
    shadow_EXMEM.opcode = IDEX.opcode;

}

void MOVN(){

    if(IDEX.rtVal != 0x0000){
        shadow_EXMEM.rv = IDEX.rsVal;
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.nop = true; //failed mov condition and thus must not operate in memory or writeback stages
    }

    shadow_EXMEM.opcode = IDEX.opcode;

}

void MOVZ(){

    if(IDEX.rtVal == 0x0000){
        shadow_EXMEM.rv = IDEX.rsVal;
        shadow_EXMEM.rd = IDEX.rd;
        shadow_EXMEM.type = IDEX.type;
    }
    else{
        shadow_EXMEM.nop = true; //failed mov condition and thus must not operate in memory or writeback stages
    }

    shadow_EXMEM.opcode = IDEX.opcode;

}

void NOP(){

    shadow_EXMEM.nop = true;

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
    BranchFlag = false;

    if(IDEX.type == N){ //NOP
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
        else if(IDEX.opcode == 0x20){ //LB
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
        if(IDEX.opcode == 0x1F){
            SEB();
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
        std::cout<<"invalid opcode or input / undocumented instruction"<<+IDEX.opcode<<std::endl;

    }
}