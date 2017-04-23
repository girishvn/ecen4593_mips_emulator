//
// Created by Girish Narayanswamy on 3/26/17.
//

/***********************************************************************************************************************

CLASS NAME: _decode

 USE: Implements the decode (ID) stage of the processor pipeline

***********************************************************************************************************************/

#include "decode.h"


using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: instType

 DESCRIPTION: Given and instruction, extracts the op-code and matches it with a instruction type (R, I, J)

 INPUTS: uint32_t inst (instruction machine code)

 OUTPUTS: void (fills IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instType(uint32_t machineCode) {

    //Extracting OP Code
    uint8_t opcode = uint8_t((0x3f) & (machineCode >> 26)); //opcode: bits 26-32

    IDEX.opcode = opcode;

    //Checking Type (R, I , J) from OP Code
    if (opcode == ROPCode) { //R-type instruction

        IDEX.type = R;
        return;
    }

    for(int i = 0; i < 17; i++){ //I-type instruction
        if(opcode == IOPCode[i]){
            IDEX.type = I;
            return;
        }
    }

    for(int j = 0; j < 2; j++){ //J-type instruction
        if(opcode == JOPCode[j]){
            IDEX.type = J;
            return;
        }
    }

    return; //invalid instruction op-code
}

/***********************************************************************************************************************

 FUNCTION NAME: instRDecode

 DESCRIPTION: Fills proper information for R-type into IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instRDecode(uint32_t machineCode) {

    IDEX.rd = uint8_t((0x1f) & (machineCode >> 11)); //rd register: bits 11-15
    IDEX.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    IDEX.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20
    IDEX.shamt =  uint8_t((0x1f) & (machineCode >> 6)); //shamt value: bits 6-10
    IDEX.funct =  uint8_t((0x3f) & (machineCode)); //function code: bits 0-5

}

/***********************************************************************************************************************

 FUNCTION NAME: instIDecode

 DESCRIPTION: Fills proper information for I-type into IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instIDecode(uint32_t machineCode) {

    IDEX.rs =  uint8_t((0x1f) & (machineCode >> 21)); //rs register: bits 21-25
    IDEX.rt =  uint8_t((0x1f) & (machineCode >> 16)); //rt register: bits 16-20
    IDEX.immediate =  uint16_t((0xffff) & (machineCode)); //immediate value: bits 0-15

}

/***********************************************************************************************************************

 FUNCTION NAME: instJDecode

 DESCRIPTION: Fills proper information for J-type into IDEX intermediate register

 INPUTS: uint32_t machineCode (instruction machine code)

 OUTPUTS: void (fills IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instJDecode(uint32_t machineCode) {

    IDEX.address =  uint32_t((0x3ffffff) & (machineCode)); //address value: bits 0-26

}

/***********************************************************************************************************************

 FUNCTION NAME: instDecode

 DESCRIPTION: Fills proper used registers

 INPUTS: uint32_t machineCode (instruction machine code), instruction *inst (instruction passed by ref from main)

 OUTPUTS: void (fills IDEX Reg with proper instruction information)

***********************************************************************************************************************/
void instDecode(uint32_t machineCode) {

    instType(machineCode); //checks type (R, I, J)
    int inst_type = IDEX.type;

    switch(inst_type) { //fills instruction based on type (R, I, J)
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
            std::cout<<"invalid opcode or input / undocumented instruction"<<std::endl;
            return;
        }
    }

}