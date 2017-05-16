//
// Created by Girish Narayanswamy on 4/19/17.
//

#include <iostream>
#include "Fetch.h"
#include "Cache.h"

/***********************************************************************************************************************

 Function Name: instFetch

 DESCRIPTION: Passes instruction machine code to intermediate register IFID

 INPUTS: void (grabs instruction mc from global memory array)

 OUTPUTS: void (fills IFID Reg with proper instruction information)

***********************************************************************************************************************/

void instFetch(void) {

    uint32_t instMC; //instruction machine code
    //instMC = uint32_t(memory[pc]); //grab correct instruction from instruction memory
    int32_t address = pc;
    instMC= uint32_t(iCacheRead(address));
    shadow_IFID.mc = instMC; //set next instruction to intermediate IF/ID register

}