//
// Created by Karros Huang on 4/23/17.
//

#include <iostream>
#include "WriteBack.h"
#include "fetch.h"

void instWriteBack(){

    if((MEMWB.rd == $v1 && MEMWB.type == R) || (MEMWB.rt == $v1 && MEMWB.type == I)){
        std::cout<<"v1"<<std::endl;
    }

    if((MEMWB.rd == 0 && MEMWB.type == R) || (MEMWB.rt == 0 && MEMWB.type == I)){
        std::cout<<"BAD WRITE: RETURN PUSH TO REG 0"<<std::endl;
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
        std::cout<<MEMWB.rv<<" "<<MEMWB.rd<<std::endl;
    }

    //Special case for Jump and Link
    if(MEMWB.type == J && MEMWB.opcode == 0x03){
        reg[$ra] = MEMWB.rv;
    }
}