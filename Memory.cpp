//
// Created by Karros Huang on 4/23/17.
//

#include "Memory.h"
#include "Decode.h"

void WriteIntoMemory(){
    memory[EXMEM.address] = EXMEM.rv;
    shadow_MEMWB.type = EXMEM.type;
    shadow_MEMWB.opcode = EXMEM.opcode;
}

void LoadFromMemory(){
    shadow_MEMWB.rv = memory[EXMEM.address];
    shadow_MEMWB.rt = EXMEM.rt;
    shadow_MEMWB.type = EXMEM.type;
    shadow_MEMWB.opcode = EXMEM.opcode;
}


void instMemory(){

    //nop instruction detection
    if(EXMEM.nop == true){ //NOP detection
        shadow_MEMWB.nop = true;
        return;
    }
    shadow_MEMWB.nop = false;

    if(EXMEM.type == I) {
        if(EXMEM.opcode == 0x24 || EXMEM.opcode == 0x25 || EXMEM.opcode == 0x30 || EXMEM.opcode == 0x23) {
            LoadFromMemory();
        }
        else if (EXMEM.opcode == 0x28 || EXMEM.opcode == 0x38 || EXMEM.opcode == 0x29 || EXMEM.opcode == 0x2b) {
            WriteIntoMemory();
        }
        else{
            shadow_MEMWB.rv = EXMEM.rv;
            shadow_MEMWB.rt = EXMEM.rt;
        }
        shadow_MEMWB.type = EXMEM.type;
    }
    else if(EXMEM.type == R){
        shadow_MEMWB.rv = EXMEM.rv;
        shadow_MEMWB.rd = EXMEM.rd;
        shadow_MEMWB.type = EXMEM.type;
        shadow_MEMWB.ra = EXMEM.ra;
    }
    else if(EXMEM.opcode == 0x03){
        shadow_MEMWB.rv = EXMEM.rv;
        shadow_MEMWB.ra = EXMEM.ra;
        shadow_MEMWB.opcode = EXMEM.opcode;
    }
}