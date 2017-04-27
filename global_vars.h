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

extern uint32_t reg[32]; //32-register system
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

memory: Total data and program image memory

***********************************************************************************************************************/

extern uint32_t memory[1200];

/***********************************************************************************************************************

 pc: program counter global variable

***********************************************************************************************************************/

extern uint32_t pc; //program counter

/***********************************************************************************************************************

Intermediate registers global structs

***********************************************************************************************************************/

struct _IFID {

    uint32_t mc = 0; //machine code of instruction

};

struct _IDEX {

    bool nop = true;;

    int type; //R, I, J

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;

    //R-type specific
    uint8_t shamt; //shamt
    uint8_t funct; //function

    //I-type specific
    uint16_t immediate;

    //J-type specific
    uint32_t address;

};

struct _EXMEM {

    bool nop = true;

    int type; //R, I, J

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    uint8_t ra;

    //R-type specific
    uint8_t shamt; //shamt
    uint8_t funct; //function

    //I-type specific
    uint16_t immediate;

    //J-type specific
    uint32_t address;

    uint32_t rv;

};

struct _MEMWB {

    bool nop = true;;

    int type; //R, I, J

    //opcode
    uint8_t opcode;

    //registers number. NOT VALUE INSIDE
    uint8_t rd;
    uint8_t rs;
    uint8_t rt;
    uint8_t ra;

    //R-type specific
    uint8_t shamt; //shamt
    uint8_t funct; //function

    //I-type specific
    uint16_t immediate;

    //J-type specific
    uint32_t address;

    uint32_t rv;

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

