//
// Created by Girish Narayanswamy on 4/19/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H
#define ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H

#include <cstdint>

//Global Variables:

/***********************************************************************************************************************

reg: Global array to hold all register memory

reg_bank_names: Enumeration to name all indices in the reg array

***********************************************************************************************************************/

extern int32_t reg[32]; //32-register system
enum reg_bank_names{
    $zero,
    $at,
    $v0,
    $v1,
    $a0,
    $a1,
    $a2,
    $a3,
    $t0,
    $t1,
    $t2,
    $t3,
    $t4,
    $t5,
    $t6,
    $t7,
    $s0,
    $s1,
    $s2,
    $s3,
    $s4,
    $s5,
    $s6,
    $s7,
    $t8,
    $t9,
    $k0,
    $k1,
    $gp,
    $sp,
    $fp,
    $ra
};

/***********************************************************************************************************************

MEMORY: Total data and program image memory

***********************************************************************************************************************/

extern int32_t memory[1200];

/***********************************************************************************************************************

 pc: program counter global variable

***********************************************************************************************************************/

extern int32_t pc; //program counter

/***********************************************************************************************************************

Intermediate registers global structs

***********************************************************************************************************************/

struct _IFID {

    uint32_t mc = 0; //machine code of instruction

};

struct _IDEX {

    //R, I, J, NOP
    int type = 0x00;

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;

    //register values
    int32_t rsVal;
    int32_t rtVal;

    //R-type specific
    uint8_t shamt; //shamt
    uint8_t funct; //function

    //I-type specific
    int16_t immediate;

    //J-type specific
    int32_t address;

};

struct _EXMEM {

    //R, I, J, NOP
    int type;

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;

    //register values
    int32_t rsVal;
    int32_t rtVal;

    //R-type specific
    uint8_t shamt; //shamt
    uint8_t funct; //function

    //I-type specific
    int16_t immediate;

    //J-type specific
    int32_t address;

    uint8_t byteIndex;
    int32_t rv;
    bool nop = true;

};

struct _MEMWB {

    int type; //R, I, J

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rt;

    int32_t rv;
    bool nop = true;;

};

//Extern Globals
extern _IFID IFID;
extern _IFID shadow_IFID;

extern _IDEX IDEX;
extern _IDEX shadow_IDEX;

extern _EXMEM EXMEM;
extern _EXMEM shadow_EXMEM;

extern _MEMWB MEMWB;
extern _MEMWB shadow_MEMWB;


#endif //ECEN4593_MIPS_EMULATOR_GLOBAL_VARS_H

