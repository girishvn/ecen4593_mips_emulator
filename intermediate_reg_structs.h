//
// Created by Girish Narayanswamy on 4/18/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_INTERMEDIATE_REG_STRUCTS_H
#define ECEN4593_MIPS_EMULATOR_INTERMEDIATE_REG_STRUCTS_H

#include <cstdint>

struct _IFID {

};

struct _IDEX {

    int type; //R, I, J

    //opcode
    uint8_t opcode;

    //registers
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

    uint32_t offset;

};

struct _MEMWB {

};




#endif //ECEN4593_MIPS_EMULATOR_INTERMEDIATE_REG_STRUCTS_H
