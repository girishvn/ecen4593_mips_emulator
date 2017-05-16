//
// Created by Girish Narayanswamy on 5/4/17.
//

#ifndef ECEN4593_MIPS_EMULATOR_CACHE_H
#define ECEN4593_MIPS_EMULATOR_CACHE_H

#include <cmath>
#include "global_vars.h"

//VARIABLES

const uint32_t iNUMBLOCKS = ICACHESIZE/4/BLOCKSIZE; //word sized blocks
const uint32_t dNUMBLOCKS = DCACHESIZE/4/BLOCKSIZE; //word sized blocks

const int32_t offsetBits = int32_t(log2(BLOCKSIZE)); //number of bits needed for block offset
const int32_t iIndexBits = int32_t(log2(iNUMBLOCKS)); //number of bits need for I cache block index
const int32_t dIndexBits = int32_t(log2(dNUMBLOCKS)); //number of bits need for D cache block index

const int32_t itagBits = 32 - offsetBits - iIndexBits;
const int32_t dtagBits = 32 - offsetBits - dIndexBits;

//FUNCTIONS

void initiCache(void);

void initdCache(void);

int tagCalc(uint32_t address, int IorD); //1 for I 2 for D
int blckIdxCalc(uint32_t address,int IorD); //1 for I 2 for D
int blckOffstCal(uint32_t address,int IorD); //1 for I 2 for D

void loadFromMem(int32_t address, int blockIndex, int blockOffset, int IorD);

int32_t iCacheRead(int32_t address);

int32_t dCacheRead(int32_t address);
void dCacheWrite(int32_t address,int32_t val);

#endif //ECEN4593_MIPS_EMULATOR_CACHE_H
