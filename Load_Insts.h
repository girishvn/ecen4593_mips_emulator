//
// Created by Girish Narayanswamy on 4/23/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_LOAD_INSTS_H
#define ECEN4593_MIPS_EMULATOR_LOAD_INSTS_H

#include "global_vars.h"

//#define PROGRAM1 //Bubble/Insertion Sort

#define PROGRAM2 //Ceasar Decipher

//#define PROGRAMLOADOPT //Optimized Program

//#define PROGRAMLOADUNOPT //Unoptimized Program

/***********************************************************************************************************************

 inst_memory_size: size of instruction memory

***********************************************************************************************************************/

extern const int inst_memory_size;

/***********************************************************************************************************************

FUNCTIONS

***********************************************************************************************************************/

void Initialize_Simulation_Memory(void);


#endif //ECEN4593_MIPS_EMULATOR_LOAD_INSTS_H
