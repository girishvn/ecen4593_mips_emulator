//
// Created by Karros Huang on 4/23/17.
//

#include "WriteBack.h"

void WriteToRegister(void){
    reg[EXMEM.rt] = Memory[EXMEM.address];
    pc++;
}