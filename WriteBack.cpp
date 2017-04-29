//
// Created by Karros Huang on 4/23/17.
//

#include "WriteBack.h"
#include "Decode.h"

void instWriteBack(){

    //nop instruction detection
    if(MEMWB.nop == true){ //NOP detection
        return;
    }

    if(MEMWB.type == I){
        reg[MEMWB.rt] = MEMWB.rv;
    }
    else if(MEMWB.type == R){
        reg[MEMWB.rd] = MEMWB.rv;
    }

    //Special case for Jump and Link
    if(MEMWB.type == J && MEMWB.opcode == 0x03){
        reg[MEMWB.ra] = MEMWB.rv;
    }
}