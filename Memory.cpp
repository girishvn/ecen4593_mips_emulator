//
// Created by Karros Huang on 4/23/17.
//

#include <iostream>
#include "Memory.h"
#include "Decode.h"
#include "Cache.h"

/***********************************************************************************************************************

CALLABLE FUNCTIONS

***********************************************************************************************************************/

/***********************************************************************************************************************

STORE WORD FUNCTIONS

***********************************************************************************************************************/

void WriteWordIntoMemory(){ //store word

    //memory[EXMEM.address] = EXMEM.rtVal;
    dCacheWrite(EXMEM.address,EXMEM.rtVal); //GIRISH
}

void WriteHalfWordIntoMemory(){
    //LOCAL VARIABLES used to properly store values into memory without overwriting unused bits
    int32_t memVal;
    uint32_t maskMem;
    uint32_t maskReg;

    //memVal = memory[EXMEM.address];
    memVal = dCacheRead(EXMEM.address); //GIRISH

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0xffff0000;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;
        }
        case 1: { //2th Byte
            maskMem = 0xff0000ff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 8;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;
        }
        case 2: { //3th Byte
            maskMem = 0x0000ffff;
            maskReg = 0x0000ffff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 16;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

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

    //memVal = memory[EXMEM.address];
    memVal = dCacheRead(EXMEM.address); //GIRISH

    switch (EXMEM.byteIndex) {
        case 0: { //1th Byte
            maskMem = 0xffffff00;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;
        }

        case 1: { //2th Byte
            maskMem = 0xffff00ff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 8;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;

        }

        case 2: { //3th Byte
            maskMem = 0xff00ffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 16;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;

        }

        case 3: { //4th Byte
            maskMem = 0x00ffffff;
            maskReg = 0x000000ff;

            memVal = maskMem & memVal;
            EXMEM.rtVal = maskReg & EXMEM.rtVal;
            EXMEM.rtVal = EXMEM.rtVal << 24;

            //memory[EXMEM.address] = memVal | EXMEM.rtVal;
            dCacheWrite(EXMEM.address,(memVal | EXMEM.rtVal)); //GIRISH

            break;

        }

        default: {
            std::cout<<"unusable index value in SH"<<std::endl;
            return;
        }
    }
}

/***********************************************************************************************************************

LOAD WORD FUNCTIONS

***********************************************************************************************************************/

void LoadWordFromMemory(void){

    //shadow_MEMWB.rv = memory[EXMEM.address];
    shadow_MEMWB.rv = dCacheRead(EXMEM.address); //GIRISH
    shadow_MEMWB.rt = EXMEM.rt;

}

void LoadHalfWordUnsignedFromMemory(void){
    //LOCAL VARIABLES
    int32_t memVal;
    uint32_t maskMem = 0x0000ffff;
    uint32_t maskSignNeg = 0xffff0000;

    //memVal = memory[EXMEM.address];
    memVal = dCacheRead(EXMEM.address); //GIRISH

    shadow_MEMWB.rt = IDEX.rt; //save register

    if(EXMEM.byteIndex < 3) {

        memVal = memVal >> 8*EXMEM.byteIndex;
        memVal = maskMem & memVal;
        if(memVal >> 15 == 1){ //sign extend with 1;
            memVal = maskSignNeg | memVal;
        }
        //else already sign extended with 0's

        shadow_MEMWB.rv = memVal;
        return;

    }

    else{ //index is 3
        std::cout<<"unusable index value in LHU"<<std::endl;
        return;
    }

}

void LoadByteSignedFromMemory(void){
    //LOCAL VARIABLES
    int32_t memVal;
    uint32_t maskMem = 0x000000ff;
    uint32_t maskSignNeg = 0xffffff00;

    //memVal = memory[EXMEM.address];
    memVal = dCacheRead(EXMEM.address);

    shadow_MEMWB.rt = IDEX.rt;

    if(EXMEM.byteIndex < 4){

        memVal = memVal >> 8*EXMEM.byteIndex;
        memVal = maskMem & memVal;
        if(memVal >> 7 == 1){ //sign extend with 1;
            memVal = maskSignNeg | memVal;
        }
        //else already sign extended with 0's

        shadow_MEMWB.rv = memVal;
        return;

    }

    else{ //index is 4
        std::cout<<"unusable index value in LB"<<std::endl;
        return;
    }

}

void LoadByteUnsignedFromMemory(void){
    //LOCAL VARIABLES
    int32_t memVal;
    uint32_t maskMem = 0x000000ff;
    uint32_t maskUnsigned = 0x000000ff;

    //memVal = memory[EXMEM.address];
    memVal = dCacheRead(EXMEM.address);
    shadow_MEMWB.rt = IDEX.rt;

    if(EXMEM.byteIndex < 4){

        memVal = memVal >> 8*EXMEM.byteIndex;
        memVal = maskMem & memVal;

        memVal = maskUnsigned | memVal;

        shadow_MEMWB.rv = memVal;
        return;

    }

    else{ //index is 4
        std::cout<<"unusable index value in LBU"<<std::endl;
        return;
    }
}

/***********************************************************************************************************************

MAIN CALLABLE FUNCTIONS

***********************************************************************************************************************/

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
            case 0x20: {
                LoadByteSignedFromMemory();
                break;
            }
            case 0x23: {
                LoadWordFromMemory();
                break;
            }
            case 0x24: {
                LoadByteUnsignedFromMemory();
                break;
            }
            case 0x25: {
                LoadHalfWordUnsignedFromMemory();
                break;
            }
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