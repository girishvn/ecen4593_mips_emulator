//
// Created by Girish Narayanswamy on 3/26/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_DECODE_H
#define ECEN4593_MIPS_EMULATOR_DECODE_H

#include "global_vars.h"
#include <iostream>

/***********************************************************************************************************************

FUNCTIONS

***********************************************************************************************************************/

//function declarations
void instRDecode(void);
void instIDecode(void);
void instJDecode(void);
void instDecode(void);
void setIDEXControl(void);
void DataHazardStall(void);
void ControlHazard(void);
void BranchForward(void);
void stallPipe(void);

//Branch Instructions
void BEQ(void); //op: 0x04
void BGTZ(void); //op: 0x07
void BLEZ(void); //op: 0x06
void BLTZ(void); //op: 0x01
void BNE(void); //op: 0x05
void JUMP(void); //op: 0x02
void JR(void); //funct: 0x08
void JAL(void); //funct: 0x03

#endif //ECEN4593_MIPS_EMULATOR_DECODE_H
