//
// Created by Karros Huang on 4/23/17.
//

#include "Memory.h"
#include "Decode.h"

void WriteIntoMemory(){
    memory[EXMEM.address] = EXMEM.rv;
}

void LoadFromMemory(){
    shadow_MEMWB.rv = memory[EXMEM.address];
    shadow_MEMWB.rt = EXMEM.rt;
    shadow_MEMWB.type = EXMEM.type;
}


void instMemory(){
    if(EXMEM.type == I) {
        if(EXMEM.opcode == 0x24 || EXMEM.opcode == 0x25 || EXMEM.opcode == 0x30 || EXMEM.opcode == 0x23) {
            LoadFromMemory();
        } else if (EXMEM.opcode == 0x28 || EXMEM.opcode == 0x38 || EXMEM.opcode == 0x29 || EXMEM.opcode == 0x2b) {
            WriteIntoMemory();
        }
    }
    else if(EXMEM.type == R){
        shadow_MEMWB.rv = EXMEM.rv;
        shadow_MEMWB.rd = EXMEM.rd;
        shadow_MEMWB.type = EXMEM.type;
    }
    else{
        std::cout<<"Memory Stage hasn't received the correct Opcode and Type"<<std::endl;
    }
}