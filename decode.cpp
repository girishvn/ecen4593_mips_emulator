//
// Created by Girish Narayanswamy on 3/26/17.
//

/***********************************************************************************************************************

CLASS NAME: _decode

 USE: Implements the decode (ID) stage of the processor pipeline

***********************************************************************************************************************/

#include "decode.h"

#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: instType

 DESCRIPTION: Given and instruction, extracts the op-code and matches it with a instruction type (R, I, J)

 INPUTS: uint32_t inst (instruction machine code), instruction *inst (instruction passed by ref)

 OUTPUTS: uint8_t type (R = 1, I = 2, J = 3)

***********************************************************************************************************************/
int instType(uint32_t machineCode, instruction *inst) {

    //Extracting OP Code
    inst->opcode = uint8_t((0x3f) & (machineCode >> 26)); //opcode: bits 26-32

    //Checking Type (R, I , J) from OP Code
    if (inst->opcode == ROPCode) { //R-type instruction
        return R;
    }

    for(int i = 0; i < 17; i++){ //I-type instruction
        if(inst->opcode == IOPCode[i]) return I;
    }

    for(int j = 0; j < 2; j++){ //J-type instruction
        if(inst->opcode == JOPCode[j]) return J;
    }

    return -1; //invalid instruction op-code
}

/***********************************************************************************************************************

 Function Name: instRDecode

 DESCRIPTION: Fills proper information for R-type

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref)

 OUTPUTS: void (returns full instruction)

***********************************************************************************************************************/
void instRDecode(uint32_t machineCode, instruction *inst) {

    inst->rd = uint8_t((0x1f) & (machineCode >> 11)); //rd register: bits 11-15
    inst->rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    inst->rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20
    inst->shamt =  uint8_t((0x1f) & (machineCode >> 6)); //shamt value: bits 6-10
    inst->funct =  uint8_t((0x3f) & (machineCode)); //function code: bits 0-5

}

/***********************************************************************************************************************

 Function Name: instIDecode

 DESCRIPTION: Fills proper information for I-type

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref)

 OUTPUTS: void (returns full instruction)

***********************************************************************************************************************/
void instIDecode(uint32_t machineCode, instruction *inst) {

    inst->rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    inst->rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20
    inst->immediate =  uint16_t((0xffff) & (machineCode)); //immediate value: bits 0-15

}

/***********************************************************************************************************************

 Function Name: instJDecode

 DESCRIPTION: Fills proper information for J-type

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref)

 OUTPUTS: void (returns full instruction)

***********************************************************************************************************************/
void instJDecode(uint32_t machineCode, instruction *inst) {

    inst->address =  uint32_t((0x3ffffff) & (machineCode)); //address value: bits 0-26

}

/***********************************************************************************************************************

 Function Name: instDecode

 DESCRIPTION: Fills proper used registers

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref from main)

 OUTPUTS: uint8_t type (R, I, J)

***********************************************************************************************************************/
void instDecode(uint32_t machineCode, instruction *inst) {

    inst->type = instType(machineCode, inst); //checks type (R, I, J)

    switch(inst->type) { //fills instruction based on type (R, I, J)
        case R: { //R-type
            instRDecode(machineCode, inst);
            return;
        }

        case I: { //I-type
            instIDecode(machineCode, inst);
            return;
        }

        case J: { //J-type
            instJDecode(machineCode, inst);
            return;
        }

        default: { //Error in input machine code
            std::cout<<"invalid opcode or input / undocumented instruction"<<std::endl;
            return;
        }
    }

}