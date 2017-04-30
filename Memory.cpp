//
// Created by Karros Huang on 4/23/17.
//

#include <iostream>
#include "Memory.h"
#include "Decode.h"

/***********************************************************************************************************************

CALLABLE FUNCTIONS

***********************************************************************************************************************/

void WriteWordIntoMemory(){

    memory[EXMEM.address] = EXMEM.rtVal;
}

void WriteHalfWordIntoMemory(){
    //LOCAL VARIABLES used to properly store values into memory without overwriting unused bits
    int32_t memVal;
    uint32_t maskMem;
    uint32_t maskReg;

    memVal = memory[EXMEM.address];

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0xffff0000;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;
        }
        case 1: { //2th Byte
            maskMem = 0xff0000ff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 8;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;
        }
        case 2: { //3th Byte
            maskMem = 0x0000ffff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 16;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;
        }
        default: { //4th Byte
            std::cout<<"unusable index value in SH"<<std::endl;
            return;
        }
    }
}


void WriteByteIntoMemory(){
    //LOCAL VARIABLES used to properly store values into memory without overwriting unused bits
    int32_t memVal;
    uint32_t maskMem;
    uint32_t maskReg;

    memVal = memory[EXMEM.address];

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0xffffff00;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0xffff00ff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 8;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0xff00ffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 16;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;

        }

        case 3: { //4th Byte
            maskMem = 0x00ffffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 24;

            memory[EXMEM.address] = memVal | EXMEM.rtVal;

            break;

        }

        default: {
            std::cout<<"unusable index value in SH"<<std::endl;
            return;
        }
    }
}

void LoadWordFromMemory(void){
    shadow_MEMWB.rv = memory[EXMEM.address];
    shadow_MEMWB.rt = EXMEM.rt;
    std::cout<<"address val: "<<EXMEM.address<<" "<<shadow_MEMWB.rv<<std::endl;
}

void LoadHalfWordFromMemory(void){
    //LOCAL VARIABLES
    int32_t memVal;
    int32_t regVal;
    uint32_t maskMem;
    uint32_t maskReg;

    regVal = EXMEM.rtVal;
    memVal = memory[EXMEM.address];
    shadow_MEMWB.rt = IDEX.rt;

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0x0000ffff;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            shadow_MEMWB.rv = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0x00ffff00;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 8;

            shadow_MEMWB.rv = memVal | regVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0xffff0000;
            maskReg = 0xffff0000;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 16;

            shadow_MEMWB.rv = memVal | regVal;

            break;

        }

        default: {
            std::cout << "unusable index value in LHU" << std::endl;
            return;
        }
    }
}

void LoadByteFromMemory(void){
    //LOCAL VARIABLES
    int32_t memVal;
    int32_t regVal;
    uint32_t maskMem;
    uint32_t maskReg;

    regVal = EXMEM.rtVal;
    memVal = memory[EXMEM.address];
    shadow_MEMWB.rt = IDEX.rt;

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0x000000ff;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;

            shadow_MEMWB.rv = memVal | regVal;

            break;
        }

        case 1: { //2th Byte
            maskMem = 0x0000ff00;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 8;

            shadow_MEMWB.rv = memVal | regVal;

            break;

        }

        case 2: { //3th Byte
            maskMem = 0x00ff0000;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 16;

            shadow_MEMWB.rv = memVal | regVal;

            break;

        }

        case 3: { //4th Byte
            maskMem = 0xff000000;
            maskReg = 0xffffff00;

            memVal = maskMem & memVal;
            regVal = maskReg & regVal;
            memVal = memVal >> 24;

            shadow_MEMWB.rv = memVal | regVal;

            break;

        }

        default: {
            std::cout<<"unusable index value in LBU"<<std::endl;
            return;
        }
    }
}

void instMemory(){

    //nop instruction detection
    if(EXMEM.nop){ //NOP detection
        shadow_MEMWB.nop = true;
        return;
    }
    shadow_MEMWB.nop = false;

    if(EXMEM.type == I) {
        switch(EXMEM.opcode){
            //Store Instructions
            case 0x28: {
                WriteByteIntoMemory();
                shadow_MEMWB.nop = true; //Store instructions skip Write Back stage
                break;
            }
            case 0x29: {
                WriteHalfWordIntoMemory();
                shadow_MEMWB.nop = true; //Store instructions skip Write Back stage
                break;
            }
            case 0x2b: {
                WriteWordIntoMemory();
                shadow_MEMWB.nop = true; //Store instructions skip Write Back stage
                break;
            }
            //Load Instructions
            case 0x0F: {

                break;
            }
            case 0x20: {

                break;
            }
            case 0x23: {
                LoadWordFromMemory();
                break;
            }
            case 0x24: {
                LoadByteFromMemory();
                break;
            }
            case 0x25: {
                LoadHalfWordFromMemory();
                break;
            }
            //I types that do not access memory
            default: {
                shadow_MEMWB.rv = EXMEM.rv;
                shadow_MEMWB.rt = EXMEM.rt;
                break;
            }
        }
    }
    else if(EXMEM.type == R){
        shadow_MEMWB.rv = EXMEM.rv;
        shadow_MEMWB.rd = EXMEM.rd;
    }
    //Special case for Jump and Link
    if(EXMEM.opcode == 0x03){
        shadow_MEMWB.rv = EXMEM.rv;
    }

    //Always pass on the type of the instruction to the next stage
    shadow_MEMWB.type = EXMEM.type;
    shadow_MEMWB.opcode = EXMEM.opcode;
}