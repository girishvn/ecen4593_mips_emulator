//
// Created by Karros Huang on 4/23/17.
//

#include "WriteBack.h"
#include "Decode.h"

void instWriteBack(){

    if(MEMWB.rd == 0 || MEMWB.rt == 0){
        std::cout<<"BAD WRITE: RETURN PUSH TO REG 0"<<std::endl;
        //reg[32] = MEMWB.rv;
        //std::cout<<+MEMWB.rd<< " " <<+MEMWB.rt<<std::endl;
        return;
    }

    //nop instruction detection
    if(MEMWB.nop){ //NOP detection
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
        reg[$ra] = MEMWB.rv;
    }
}