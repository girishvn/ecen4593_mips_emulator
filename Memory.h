//
// Created by Karros Huang on 4/23/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_MEMORY_H
#define ECEN4593_MIPS_EMULATOR_MEMORY_H

#include "global_vars.h"

void WriteWordIntoMemory();
void WriteHalfWordIntoMemory();
void WriteByteIntoMemory();

void LoadWordFromMemory(void);
void LoadHalfWordFromMemory(void);
void LoadByteUnsignedFromMemory(void);
void LoadByteSignedFromMemory(void);
void instMemory(void);

#endif //ECEN4593_MIPS_EMULATOR_MEMORY_H
