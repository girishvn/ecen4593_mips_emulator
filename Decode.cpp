//
// Created by Girish Narayanswamy on 3/26/17.
//

/***********************************************************************************************************************

CLASS NAME: Decode

 USE: Implements the decode (ID) stage of the processor pipeline

***********************************************************************************************************************/

#include "Decode.h"

using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: instType

 DESCRIPTION: Given and instruction, extracts the op-code and matches it with a instruction type (R, I, J)

 INPUTS: uint32_t inst (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instType(uint32_t machineCode) {

    //Extracting OP Code
    uint8_t opcode = uint8_t((0x3f) & (machineCode >> 26)); //opcode: bits 26-32

    shadow_IDEX.opcode = opcode;

    //Checking Type (R, I , J) from OP Code
    if(machineCode == 0x00000000){

        shadow_IDEX.type = N;
        return;
    }
    else if (opcode == ROPCode || opcode == sebOPCode) { //R-type instruction

        shadow_IDEX.type = R;
        return;
    }

    for(int i = 0; i < 20; i++){ //I-type instruction
        if(opcode == IOPCode[i]){
            shadow_IDEX.type = I;
            return;
        }
    }

    for(int j = 0; j < 2; j++){ //J-type instruction
        if(opcode == JOPCode[j]){
            shadow_IDEX.type = J;
            return;
        }
    }

    return; //invalid instruction op-code
}

/***********************************************************************************************************************

 FUNCTION NAME: instRDecode

 DESCRIPTION: Fills proper information for R-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instRDecode(uint32_t machineCode) {

    //used registers
    shadow_IDEX.rd = uint8_t((0x1f) & (machineCode >> 11)); //rd register: bits 11-15
    shadow_IDEX.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    shadow_IDEX.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20

    //reg values
    shadow_IDEX.rsVal = reg[shadow_IDEX.rs];
    shadow_IDEX.rtVal = reg[shadow_IDEX.rt];

    //other parameters
    shadow_IDEX.shamt =  uint8_t((0x1f) & (machineCode >> 6)); //shamt value: bits 6-10
    shadow_IDEX.funct =  uint8_t((0x3f) & (machineCode)); //function code: bits 0-5

}

/***********************************************************************************************************************

 FUNCTION NAME: instIDecode

 DESCRIPTION: Fills proper information for I-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instIDecode(uint32_t machineCode) {

    //used registers
    shadow_IDEX.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    shadow_IDEX.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20

    //reg values
    shadow_IDEX.rsVal = reg[shadow_IDEX.rs];
    shadow_IDEX.rtVal = reg[shadow_IDEX.rt];
    //other parameters
    shadow_IDEX.immediate =  uint16_t((0xffff) & (machineCode)); //immediate value: bits 0-15

}

/***********************************************************************************************************************

 FUNCTION NAME: instJDecode

 DESCRIPTION: Fills proper information for J-type into shadow_IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instJDecode(uint32_t machineCode) {

    //other parameters
    shadow_IDEX.address =  uint32_t((0x3ffffff) & (machineCode)); //address value: bits 0-26

}

/***********************************************************************************************************************

 FUNCTION NAME: instDecode

 DESCRIPTION: Fills proper used registers

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref from main)

 OUTPUTS: void (fills shadow_IDEX Reg with proper instruction information)

***********************************************************************************************************************/

/***********************************************************************************************************************

 FUNCTION NAME: setcontrol

 DESCRIPTION: sets the controls for each specific type of opcode that will propogate through the pipeline

 INPUTS: opcode

 OUTPUTS: control line booleans

***********************************************************************************************************************/

void setcontrol(){
    //set control lines depending on opcode
    //R-types
    if((shadow_IDEX.opcode == 0x00) || (shadow_IDEX.opcode == 0x1F)){
        shadow_IDEX.regDst = true;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
    }
    //loads
    else if((shadow_IDEX.opcode == 0x20) || (shadow_IDEX.opcode == 0x24) || (shadow_IDEX.opcode == 0x25)
       || (shadow_IDEX.opcode == 0x0F) || (shadow_IDEX.opcode == 0x23) ){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = true;
        shadow_IDEX.memToReg = true;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.memRead = true;
        shadow_IDEX.memWrite = false;
    }
    //stores
    else if((shadow_IDEX.opcode == 0x28) || (shadow_IDEX.opcode == 0x29) || (shadow_IDEX.opcode == 0x2B) ){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = true;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = true;
    }
    //branches
    else if((shadow_IDEX.opcode == 0x4) || (shadow_IDEX.opcode == 0x5) || (shadow_IDEX.opcode == 0x6)
       || (shadow_IDEX.opcode == 0x7) || (shadow_IDEX.opcode == 0x1) || (shadow_IDEX.opcode == 0x2)
       || (shadow_IDEX.opcode == 0x3) || ((shadow_IDEX.opcode == 0x00) && (shadow_IDEX.funct == 0x8))){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = false;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
    }
    //immediates
    else if((shadow_IDEX.opcode == 0x8)||(shadow_IDEX.opcode == 0x9)||(shadow_IDEX.opcode == 0xC)
       ||(shadow_IDEX.opcode == 0xE)||(shadow_IDEX.opcode == 0xA)||(shadow_IDEX.opcode == 0xB)
       ||(shadow_IDEX.opcode == 0xD)){
        shadow_IDEX.regDst = false;
        shadow_IDEX.ALUSrc = false;
        shadow_IDEX.memToReg = false;
        shadow_IDEX.regWrite = true;
        shadow_IDEX.memRead = false;
        shadow_IDEX.memWrite = false;
    }
}

void instDecode(void) {

    //delayed branch
    if(BranchFlag){
        pc = BranchPC;
    }
    else{
        pc++; //increment PC in decode
    }

    uint32_t machineCode = IFID.mc;

    instType(machineCode); //checks type (R, I, J) and gets opcode
    int inst_type = shadow_IDEX.type;

    setcontrol(); //Set control bits based on the decoded opcode.

    switch(inst_type) { //fills instruction based on type (nop, R, I, J)
        case N: {
            return;
        }
        case R: { //R-type
            instRDecode(machineCode);
            return;
        }
        case I: { //I-type
            instIDecode(machineCode);
            return;
        }
        case J: { //J-type
            instJDecode(machineCode);
            return;
        }
        default: { //Error in input machine code
            cout << "invalid opcode or input / undocumented instruction" << endl;
            return;
        }
    }
}