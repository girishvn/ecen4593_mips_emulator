//
// Created by Karros Huang on 4/23/17.
//

#include "WriteBack.h"
#include "Decode.h"

void instWriteBack(){
    if(MEMWB.type == I){
        reg[MEMWB.rt] = MEMWB.rv;
    }
    else if(MEMWB.type == R){
        reg[MEMWB.rd] = MEMWB.rv;
    }
}