//
// Created by Girish Narayanswamy on 3/26/17.
//

/***********************************************************************************************************************

CLASS NAME: Decode

 USE: Implements the decode (ID) stage of the processor pipeline

***********************************************************************************************************************/

#include "Decode.h"
#include "Fetch.h"

using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: instRDecode

 DESCRIPTION: Fills proper information for R-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instRDecode(void) {

    //reg values
    shadow_IDEX.rsVal = reg[IFID.rs];
    shadow_IDEX.rtVal = reg[IFID.rt];
    shadow_IDEX.rd = IFID.rd;
    shadow_IDEX.rs = IFID.rs;
    shadow_IDEX.rt = IFID.rt;

    //other parameters
    shadow_IDEX.shamt =  IFID.shamt; //shamt value: bits 6-10
    shadow_IDEX.funct =  IFID.funct; //function code: bits 0-5

}

/***********************************************************************************************************************

 FUNCTION NAME: instIDecode

 DESCRIPTION: Fills proper information for I-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instIDecode(void) {

    //reg values
    shadow_IDEX.rsVal = reg[IFID.rs];
    shadow_IDEX.rtVal = reg[IFID.rt];
    shadow_IDEX.rs = IFID.rs;
    shadow_IDEX.rt = IFID.rt;
    //other parameters
    shadow_IDEX.immediate =  IFID.immediate; //immediate value: bits 0-15

}

/***********************************************************************************************************************

 FUNCTION NAME: instJDecode

 DESCRIPTION: Fills proper information for J-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instJDecode(void) {

    //other parameters
    shadow_IDEX.address = IFID.address; //address value: bits 0-26

}

/***********************************************************************************************************************

BRANCH FUNCTIONS

***********************************************************************************************************************/
//NOTE: IF PC IS INCREMENTED IN FETCH INSTEAD OF EXECUTE: GET RID OF +1 INCREMENTATION OF PC IN BRANCHES AND JUMPS


void BEQ(){ //good

    if(shadow_IDEX.rsVal == shadow_IDEX.rtVal){
        pcNext = pc + shadow_IDEX.immediate;
    }

    shadow_IDEX.nop = true;

}

void BGTZ(){ //good

    if(shadow_IDEX.rsVal > 0){
        pcNext = pc + shadow_IDEX.immediate;
    }

    shadow_IDEX.nop = true;

}

void BLEZ(){ //good

    if(shadow_IDEX.rsVal <= 0){
        pcNext = pc + shadow_IDEX.immediate;
    }

    shadow_IDEX.nop = true;

}

void BLTZ(){ //good

    if(shadow_IDEX.rsVal < 0){
        pcNext = pc + shadow_IDEX.immediate;
    }

    shadow_IDEX.nop = true;

}

void BNE(){ //good

    if(shadow_IDEX.rsVal != shadow_IDEX.rtVal){
        pcNext = pc + shadow_IDEX.immediate;
    }

    shadow_IDEX.nop = true;

}

/***********************************************************************************************************************

JUMP FUNCTIONS

***********************************************************************************************************************/

void JUMP(){ //good

    int32_t npc;
    npc = ((4*pc) & 0xf0000000) | (shadow_IDEX.address << 2);
    pcNext = npc >> 2;

    shadow_IDEX.nop = true; //no mem-access or write back

}

void JAL(){ //good

    shadow_IDEX.rv = (pc + 1)*4;

    int32_t npc;
    npc = ((4*pc) & 0xf0000000) | (IDEX.address << 2);
    pcNext = npc >> 2;
    shadow_IDEX.opcode = IFID.opcode;
    shadow_IDEX.type = IFID.type;

}

void JR(){ //good

    int32_t npc;
    npc = shadow_IDEX.rsVal;
    pcNext = npc >> 2;

    shadow_IDEX.nop = true; //no mem-access or write back

}

/***********************************************************************************************************************

 FUNCTION NAME: setIDEXcontrol

 DESCRIPTION: sets the controls for each specific type of opcode that will propogate through the pipeline

 INPUTS: opcode

 OUTPUTS: control line booleans

***********************************************************************************************************************/

void setIDEXControl(){
    //set control lines depending on opcode
    //R-types
    if((shadow_IFID.opcode == 0x00) || (shadow_IFID.opcode == 0x1F)){
        shadow_IDEX.regDst = true;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
        shadow_IDEX.isBranch = false;
    }

    //loads
    else if((shadow_IFID.opcode == 0x20) || (shadow_IFID.opcode == 0x24) || (shadow_IFID.opcode == 0x25)
       || (shadow_IFID.opcode == 0x0F) || (shadow_IFID.opcode == 0x23) ){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = true;
        shadow_IDEX.memToReg = true;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.memRead = true;
        shadow_IDEX.memWrite = false;
        shadow_IDEX.isBranch = false;
    }

    //stores
    else if((shadow_IFID.opcode == 0x28) || (shadow_IFID.opcode == 0x29) || (shadow_IFID.opcode == 0x2B) ){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = true;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = true;
        shadow_IDEX.isBranch = false;
    }

    //branches
    else if((shadow_IFID.opcode == 0x4) || (shadow_IFID.opcode == 0x5) || (shadow_IFID.opcode == 0x6)
       || (shadow_IFID.opcode == 0x7) || (shadow_IFID.opcode == 0x1) || (shadow_IFID.opcode == 0x2)
       || (shadow_IFID.opcode == 0x3) || ((shadow_IFID.opcode == 0x00) && (shadow_IFID.funct == 0x8))){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
        shadow_IDEX.isBranch = true;
    }

    //immediates
    else if((shadow_IFID.opcode == 0x8)||(shadow_IFID.opcode == 0x9)||(shadow_IFID.opcode == 0xC)
       ||(shadow_IFID.opcode == 0xE)||(shadow_IFID.opcode == 0xA)||(shadow_IFID.opcode == 0xB)
       ||(shadow_IFID.opcode == 0xD)){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
        shadow_IDEX.isBranch = false;
    }
}

/***********************************************************************************************************************

 FUNCTION NAME: stallPipe

 DESCRIPTION: stall the pipe by setting all controls to 0 and raising stall flag

 INPUTS: void

 OUTPUTS: boolean for stall

***********************************************************************************************************************/

void stallPipe(){
    shadow_IDEX.regDst = true;
    shadow_IDEX.regWrite = true;
    shadow_IDEX.ALUSrc = false;
    shadow_IDEX.memToReg = false;
    shadow_IDEX.memRead = false;
    shadow_IDEX.memWrite = false;
    shadow_IDEX.isBranch = false;
    stall = true;
}

/***********************************************************************************************************************

 FUNCTION NAME: Execute hazards & Branch forwarding

 DESCRIPTION: combo of branch forwarding and execute hazards

 INPUTS: shadow_IDEX.memRead, IDEX.rt, IFID.rs, IDEX.rt, IDFID

 OUTPUTS: forward boolean and rt/rs val

***********************************************************************************************************************/

void BranchForward(){
    if(shadow_IDEX.isBranch && (EXMEM.regWrite)
       && !(EXMEM.memRead) && (EXMEM.rs != 0 || EXMEM.rt != 0)
       && (EXMEM.rs == IFID.rs)){  // Forwarding and hazards
        shadow_IDEX.rsVal = EXMEM.rv;
        fwd = true;
    }
    if(shadow_IDEX.isBranch && (EXMEM.regWrite)
       && !(EXMEM.memRead) && (EXMEM.rs != 0 || EXMEM.rt != 0)
       && (EXMEM.rt == IFID.rt)) {
        shadow_IDEX.rtVal = EXMEM.rv;
        fwd = true;
    }
}

/***********************************************************************************************************************

 FUNCTION NAME: Data Hazard Stall

 DESCRIPTION: if theres a data hazard, stall the program. happens when lw is followed by a r or i type using the same regisers

 INPUTS: shadow_IDEX.memRead, IDEX.rt, IFID.rs, IDEX.rt, IDFID

 OUTPUTS: stall or no stall

***********************************************************************************************************************/

void DataHazardStall(){
    if(IDEX.memRead && ((IDEX.rt == IFID.rs) || (IDEX.rt == IFID.rt))){

       stallPipe(); //inserting a nop in the ID/EX stage to propogate through

    }
}

/***********************************************************************************************************************

 FUNCTION NAME: Control Hazard Stall

 DESCRIPTION: if theres a control hazard, stall the program. happens with branches.

 INPUTS: shadow_IDEX.memRead, IDEX.rt, IFID.rs, IDEX.rt, IDFID

 OUTPUTS: stall or no stall

***********************************************************************************************************************/

void ControlHazard(){
    if(shadow_IDEX.isBranch && IDEX.regWrite && ((IDEX.rd != 0) || (IDEX.rs != 0))
       && ((IDEX.rt == IFID.rt) || (IDEX.rs == IFID.rs))){

        stallPipe();

    }
    else if(shadow_IDEX.isBranch && !(fwd) && (EXMEM.regWrite) && (EXMEM.memRead) && ((EXMEM.rd != 0) || (EXMEM.rs != 0))
            && ((EXMEM.rt == IFID.rt) || (EXMEM.rs == IFID.rs))){
        stallPipe();

    }
}

/***********************************************************************************************************************

 FUNCTION NAME: instDecode

 DESCRIPTION: Fills proper used registers

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref from main)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/

void instDecode(void) {

    if(IFID.nop) { //NOP detection
        shadow_IDEX.nop = true;
        return;
    }

    setIDEXControl(); //Set control bits based on the decoded opcode.

    shadow_IDEX.type = IFID.type;

    switch(IFID.type) { //fills instruction based on type (nop, R, I, J)
        case N: {
            break;
        }
        case R: { //R-type
            instRDecode();
            break;
        }
        case I: { //I-type
            instIDecode();
            shadow_IDEX.opcode = IFID.opcode;
            break;
        }
        case J: { //J-type
            instJDecode();
            shadow_IDEX.opcode = IFID.opcode;
            break;
        }
        default: { //Error in input machine code
            cout << "invalid opcode or input / undocumented instruction" << endl;
            break;
        }

    }
    //Branch
    BranchForward();
    //Is there a control hazard?
    ControlHazard();
    //Is there a data hazard stall?
    DataHazardStall();

    //Decoded a branch instruction, now do the branch
    if(shadow_IDEX.isBranch){
        switch(shadow_IDEX.opcode){
            case 0x04: { //BEQ
                BEQ();
                break;
            }
            case 0x07: { //BEQ
                BGTZ();
                break;
            }
            case 0x06: { //BEQ
                BLEZ();
                break;
            }
            case 0x01: { //BEQ
                BLTZ();
                break;
            }
            case 0x05: { //BEQ
                BNE();
                break;
            }
            case 0x02: { //BEQ
                JUMP();
                break;
            }
            case 0x03: { //BEQ
                JAL();
                break;
            }
            case 0x08: { //BEQ
                JR();
                break;
            }
        }
    }
    fwd = false;
}