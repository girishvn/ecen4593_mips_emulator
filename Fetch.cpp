//
// Created by Girish Narayanswamy on 4/19/17.
//

#include <iostream>
#include "Fetch.h"

/***********************************************************************************************************************

 FUNCTION NAME: instType

 DESCRIPTION: Given and instruction, extracts the op-code and matches it with a instruction type (R, I, J)

 INPUTS: uint32_t inst (instruction machine code)

 OUTPUTS: void (fills shadow_IFID Reg with proper instruction information)

***********************************************************************************************************************/
void instType(uint32_t machineCode) {

    //Extracting OP Code
    uint8_t opcode = uint8_t((0x3f) & (machineCode >> 26)); //opcode: bits 26-32

    shadow_IFID.opcode = opcode;

    //Checking Type (R, I , J) from OP Code
    if(machineCode == 0x00000000){

        shadow_IFID.type = N;
        return;
    }
    else if (opcode == ROPCode || opcode == sebOPCode) { //R-type instruction

        shadow_IFID.type = R;
        return;
    }

    for(int i = 0; i < 20; i++){ //I-type instruction
        if(opcode == IOPCode[i]){
            shadow_IFID.type = I;
            return;
        }
    }

    for(int j = 0; j < 2; j++){ //J-type instruction
        if(opcode == JOPCode[j]){
            shadow_IFID.type = J;
            return;
        }
    }

    return; //invalid instruction op-code
}

/***********************************************************************************************************************

 FUNCTION NAME: instRDecode

 DESCRIPTION: Fills proper information for R-type into shadow_IFID intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IFID Reg with proper instruction information)

***********************************************************************************************************************/
void instRDecode(uint32_t machineCode) {

    //used registers
    shadow_IFID.rd = uint8_t((0x1f) & (machineCode >> 11)); //rd register: bits 11-15
    shadow_IFID.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    shadow_IFID.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20

    //other parameters
    shadow_IFID.shamt =  uint8_t((0x1f) & (machineCode >> 6)); //shamt value: bits 6-10
    shadow_IFID.funct =  uint8_t((0x3f) & (machineCode)); //function code: bits 0-5

}

/***********************************************************************************************************************

 FUNCTION NAME: instIDecode

 DESCRIPTION: Fills proper information for I-type into shadow_IFID intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IFID Reg with proper instruction information)

***********************************************************************************************************************/
void instIDecode(uint32_t machineCode) {

    //used registers
    shadow_IFID.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    shadow_IFID.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20

    //other parameters
    shadow_IFID.immediate =  uint16_t((0xffff) & (machineCode)); //immediate value: bits 0-15

}

/***********************************************************************************************************************

 FUNCTION NAME: instJDecode

 DESCRIPTION: Fills proper information for J-type into shadow_IFID intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills shadow_IFID Reg with proper instruction information)

***********************************************************************************************************************/
void instJDecode(uint32_t machineCode) {

    //other parameters
    shadow_IFID.address =  uint32_t((0x3ffffff) & (machineCode)); //address value: bits 0-26

}

/***********************************************************************************************************************

 Function Name: instFetch

 DESCRIPTION: Passes instruction machine code to intermediate register IFID

 INPUTS: void (grabs instruction mc from global memory array)

 OUTPUTS: void (fills IFID Reg with proper instruction information)

***********************************************************************************************************************/

void instFetch(void) {

    stall = false;

    uint32_t machineCode; //instruction machine code
    machineCode = uint32_t(memory[pc]); //grab correct instruction from instruction memory
    shadow_IFID.mc = machineCode; //set next instruction to intermediate IF/ID register

    instType(machineCode); //checks type (R, I, J) and gets opcode

    int inst_type = shadow_IFID.type;

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
            std::cout << "invalid opcode or input / undocumented instruction" << std::endl;
            return;
        }
    }

}