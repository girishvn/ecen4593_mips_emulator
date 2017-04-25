//
// Created by Karros Huang on 4/23/17.
//

#include "Memory.h"

void WriteIntoMemory(){
    memory[EXMEM.address] = EXMEM.rv;
    pc++;
}
