#include <iostream>

#include "global_vars.h"
#include "Load_Program.h"
#include "decode.h"

using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: instFetch

 DESCRIPTION: Passes instruction machine code to intermediate register IFID

 INPUTS: void (grabs instruction mc from global memory array)

 OUTPUTS: void (fills IFID Reg with proper instruction information)

***********************************************************************************************************************/

void escapeShadowRealm(void) { //the shadow realm is always void

    IFID = shadow_IFID;
    IDEX = shadow_IDEX;
    EXMEM = shadow_EXMEM;
    MEMWB = shadow_MEMWB;

}

/***********************************************************************************************************************

 FUNCTION NAME: main

 DESCRIPTION: Simulates a MIPS processor for a given program found in Load_Program.h

 INPUTS: void

 OUTPUTS: int (1 exited correctly)

***********************************************************************************************************************/

int main() {

    //init all values for operation:
    Initialize_Simulation_Memory(); //copy program image into memory array
    pc = memory[5]; //set program counter value
    reg[$sp] = memory[0]; //init stack pointer
    reg[$fp] = memory[1]; //init frame pointer


    while(pc != 0x00000000){ //while PC does not jump to 0x000 (end of file)

        escapeShadowRealm(); //transfer data from shadow registers to real registers
    }

/***********************************************************************************************************************

TEST CODE

***********************************************************************************************************************/

    uint32_t mc = 0x00ff2244; //test machine code

    instDecode(mc); //calling ID stage of pipeline

    std::cout <<"type: "<<IDEX.type<< std::endl;
    std::cout <<"rd: "<<int(IDEX.rd)<< std::endl;
    std::cout <<"rs: "<<int(IDEX.rs)<< std::endl;
    std::cout <<"rt: "<<int(IDEX.rt)<< std::endl;

    /*
    uint16_t tst = 0xffaa;
    int16_t signedtst = int16_t(tst);

    std::cout <<"unsigned 16 bit val: "<<int(IDEX.rs)<< std::endl;
    std::cout <<"2signed 16 bit val: "<<int(IDEX.rt)<< std::endl;
    */

    return 1;

}