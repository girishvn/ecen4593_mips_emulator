//
// Created by Girish Narayanswamy on 5/4/17.
//

#include <iostream>
#include "Cache.h"

/***********************************************************************************************************************

CLASS NAME: CACHE

 USE: Implements the decode (ID) stage of the processor pipeline

***********************************************************************************************************************/

/***********************************************************************************************************************

 FUNCTION NAME: initiCache GOOD

 DESCRIPTION: Build instruction cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void initiCache(void){

    iCache.numBlocks = iNUMBLOCKS; //sets number of blocks
    iCache.blockArr = (_BLOCK *) malloc(iNUMBLOCKS*sizeof(_BLOCK)); //init block array

    for(int i = 0; i < iNUMBLOCKS; i++){
        iCache.blockArr[i].valid = 0;
        iCache.blockArr[i].tag = 0;
    }
}

/***********************************************************************************************************************

 FUNCTION NAME: initdCache GOOD

 DESCRIPTION: Build data cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void initdCache(void){

    iCache.numBlocks = dNUMBLOCKS; //sets number of blocks
    dCache.blockArr = (_BLOCK *) malloc(dNUMBLOCKS*sizeof(_BLOCK)); //init block array

    for(int i = 0; i < dNUMBLOCKS; i++){
        dCache.blockArr[i].valid = 0;
        dCache.blockArr[i].tag = 0;
    }
}

/***********************************************************************************************************************

 FUNCTION NAME: tagCalc GOOD

 DESCRIPTION: Calculates tag to search for in cache

 INPUTS: int32_t address, int IorD

 OUTPUTS: int tag value

***********************************************************************************************************************/

int tagCalc(uint32_t address, int IorD) {

    uint32_t tag;

    if(IorD == 1){ //i cache
        tag = address >> (32 - itagBits);
    }
    else if(IorD == 0){ //D cache
        tag = address >> (32 - dtagBits);
    }
    else{
        std::cout<<"NOT I OR D TYPE CACHE ACCESS"<<std::endl;
        return 0;
    }

    return tag;
}

/***********************************************************************************************************************

 FUNCTION NAME: blckIdxCalc GOOD

 DESCRIPTION: Calculates tag to search for in cache

 INPUTS: int32_t address, int IorD

 OUTPUTS: int block index value

***********************************************************************************************************************/

int blckIdxCalc(uint32_t address,int IorD) {

    uint32_t blckIdx;

    if(IorD == 1){ //i cache
        blckIdx = address >> offsetBits; //shift off offset bits
        blckIdx = blckIdx << (offsetBits + itagBits); //shift off tag bits
        blckIdx = blckIdx >> (offsetBits + itagBits); //shift blckIdx all the way to the bottom bits
    }
    else if(IorD == 0){ //D cache
        blckIdx = address >> offsetBits; //shift off offset bits
        blckIdx = blckIdx << (offsetBits + dtagBits); //shift off tag bits
        blckIdx = blckIdx >> (offsetBits + dtagBits); //shift blckIdx all the way to the bottom bits
    }
    else{
        std::cout<<"NOT I OR D TYPE CACHE ACCESS"<<std::endl;
        return 0;
    }

    return blckIdx;
}

/***********************************************************************************************************************

 FUNCTION NAME: blckIdxCalc GOOD

 DESCRIPTION: Calculates tag to search for in cache

 INPUTS: int32_t address, int IorD

 OUTPUTS: int block index value

***********************************************************************************************************************/

int blckOffstCal(uint32_t address,int IorD) {

    uint32_t blckOffst;

    if(offsetBits == 0){ //cannot shift 32 bits in C
        return 0;
    }

    if(IorD == 1){ //i cache
        blckOffst = address << (32 - offsetBits); //shift off tag bits and index bits
        blckOffst = blckOffst >> (32 - offsetBits); //shift blckIdx all the way to the bottom bits
    }
    else if(IorD == 0){ //D cache
        blckOffst = address << (32 - offsetBits); //shift off tag bits and index bits
        blckOffst = blckOffst >> (32 - offsetBits); //shift blckIdx all the way to the bottom bits
    }
    else{
        std::cout<<"NOT I OR D TYPE CACHE ACCESS"<<std::endl;
        return 0;
    }

    return blckOffst;
}

/***********************************************************************************************************************

 FUNCTION NAME: loadFromMem

 DESCRIPTION: Build instruction cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void loadFromMem(int32_t address, int blockIndex, int blockOffset, int IorD){


    if(IorD == 1) { //i cache
        for (int i = 0; i < BLOCKSIZE; i++) { //load entire block of instructions from mem
            iCache.blockArr[blockIndex].entryArr[i] = memory[address + i - blockOffset]; //load word from mem
        }
        ClockCycles = ClockCycles + 8 + 2*(BLOCKSIZE - 1) - 1;
    }
    else if(IorD == 0){ //D cache
        for (int i = 0; i < BLOCKSIZE; i++) { //load entire block of instructions from mem
            dCache.blockArr[blockIndex].entryArr[i] = memory[address + i - blockOffset]; //load word from mem
        }
        ClockCycles = ClockCycles + 8 + 2*(BLOCKSIZE - 1) - 1;
    }
    else{
        std::cout<<"NOT I OR D TYPE CACHE ACCESS"<<std::endl;
    }

    return;

}

/***********************************************************************************************************************

 FUNCTION NAME: iCacheRead GOOD

 DESCRIPTION: Build instruction cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

int32_t iCacheRead(int32_t address){
    iaccesses++;

    int32_t readVal;

    int tag = tagCalc(uint32_t(address),1); //calculates tag
    int blockIndex = blckIdxCalc(uint32_t(address),1); //calculates block index
    int blockOffset = blckOffstCal(uint32_t(address),1); //calculates block offset

    if(iCache.blockArr[blockIndex].valid == 0){ //if valid bit not set

        loadFromMem(address,blockIndex,blockOffset,1);
        iCache.blockArr[blockIndex].tag = tag;
        iCache.blockArr[blockIndex].valid = 1;
        readVal = iCache.blockArr[blockIndex].entryArr[blockOffset]; //return first val in newly filled block

    }
    else if(iCache.blockArr[blockIndex].tag == tag){ //if memory is correct in cache
        ihits++;
        readVal = iCache.blockArr[blockIndex].entryArr[blockOffset];
    }
    else { //else
        loadFromMem(address,blockIndex,blockOffset,1);
        iCache.blockArr[blockIndex].tag = tag;
        iCache.blockArr[blockIndex].valid = 1;
        readVal = iCache.blockArr[blockIndex].entryArr[blockOffset]; //return first val in newly filled block
    }

    return readVal;
}

/***********************************************************************************************************************

 FUNCTION NAME: dCacheRead

 DESCRIPTION: Build instruction cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

int32_t dCacheRead(int32_t address){
    daccesses++;

    int32_t readVal;

    int tag = tagCalc(uint32_t(address),0); //calculates tag
    int blockIndex = blckIdxCalc(uint32_t(address),0); //calculates block index
    int blockOffset = blckOffstCal(uint32_t(address),0); //calculates block offset

    if(dCache.blockArr[blockIndex].valid == 0){ //if valid bit not set

        loadFromMem(address,blockIndex,blockOffset,0);
        dCache.blockArr[blockIndex].tag = tag;
        dCache.blockArr[blockIndex].valid = 1;
        dCache.blockArr[blockIndex].dirty = 0;
        readVal = dCache.blockArr[blockIndex].entryArr[blockOffset]; //return first val in newly filled block

    }
    else if(dCache.blockArr[blockIndex].tag == tag){ //if memory is correct in cache
        dhits++;
        dCache.blockArr[blockIndex].tag = tag;
        readVal = dCache.blockArr[blockIndex].entryArr[blockOffset];
    }
    else { //else
        loadFromMem(address,blockIndex,blockOffset,0);
        dCache.blockArr[blockIndex].tag = tag;
        dCache.blockArr[blockIndex].valid = 1;
        dCache.blockArr[blockIndex].dirty = 0;
        readVal = dCache.blockArr[blockIndex].entryArr[blockOffset]; //return first val in newly filled block
    }

    return readVal;
}

/***********************************************************************************************************************

 FUNCTION NAME: dCacheWrite

 DESCRIPTION: Build instruction cache

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void dCacheWrite(int32_t address, int32_t val){
    daccesses++;

    int tag = tagCalc(uint32_t(address),0); //calculates tag
    int blockIndex = blckIdxCalc(uint32_t(address),0); //calculates block index
    int blockOffset = blckOffstCal(uint32_t(address),0); //calculates block offset

    if(dCache.blockArr[blockIndex].tag == tag && dCache.blockArr[blockIndex].dirty == 1) { //address correct but dirty data

        memory[address] = dCache.blockArr[blockIndex].entryArr[blockOffset]; //push to memory
    }

    if(dCache.blockArr[blockIndex].tag == tag){
        dhits++;
        dCache.blockArr[blockIndex].entryArr[blockOffset] = val;
    }
    else {
        loadFromMem(address,blockIndex,blockOffset,0); //if address incorrect pull from memory
        dCache.blockArr[blockIndex].tag = tag; //set tag
        dCache.blockArr[blockIndex].valid = 1; //set valid

        dCache.blockArr[blockIndex].entryArr[blockOffset] = val; //store value
    }


    if(writeThrough == true) {
        memory[address] = val;
        ClockCycles = ClockCycles + 6 - 1;
        dCache.blockArr[blockIndex].dirty = 0;
    }
    else {
        dCache.blockArr[blockIndex].dirty = 1;
    }

    return;
}