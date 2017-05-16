#include <iostream>

#include "global_vars.h"
#include "Load_Insts.h"
#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "Memory.h"
#include "WriteBack.h"
#include "Cache.h"

using namespace std;

/***********************************************************************************************************************

 FUNCTION NAME: thePurge

 DESCRIPTION: Re-initilizes all intermediate register values

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void thePurge(void){

    //IFID
    shadow_IFID.mc = 0;

    //IDEX
    shadow_IDEX.type = 0;
    shadow_IDEX.opcode = 0;
    shadow_IDEX.rd = 32;
    shadow_IDEX.rs = 32;
    shadow_IDEX.rt = 32;
    shadow_IDEX.rsVal = 0;
    shadow_IDEX.rtVal = 0;
    shadow_IDEX.immediate = 0;
    shadow_IDEX.address = 0;

    //EXMEM
    shadow_EXMEM.type = 0;
    shadow_EXMEM.opcode = 0;
    shadow_EXMEM.rd = 32;
    shadow_EXMEM.rs = 32;
    shadow_EXMEM.rt = 32;
    shadow_EXMEM.rsVal = 0;
    shadow_EXMEM.rtVal = 0;
    shadow_EXMEM.immediate = 0;
    shadow_EXMEM.address = 0;
    shadow_EXMEM.byteIndex = 0;
    shadow_EXMEM.rv = 0;
    shadow_EXMEM.nop = false;

    //MEMWB
    shadow_MEMWB.type = 0;
    shadow_MEMWB.opcode = 0;
    shadow_MEMWB.rd = 32;
    shadow_MEMWB.rt = 32;
    shadow_MEMWB.rv = 0;
    shadow_MEMWB.nop = false;

}

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

    thePurge(); //inits all intermediate register vaues

}

/***********************************************************************************************************************

 FUNCTION NAME: main

 DESCRIPTION: Simulates a MIPS processor for a given program found in Load_Program.h

 INPUTS: void

 OUTPUTS: int (1 exited correctly)

***********************************************************************************************************************/

int main() {

    thePurge(); //init all values for operation:
    Initialize_Simulation_Memory(); //copy program image into memory array
    initiCache(); //init Instruction Cache
    initdCache(); //init Data Cache

    pc = memory[5]; //set program counter value
    reg[$sp] = memory[0]; //init stack pointer
    reg[$fp] = memory[1]; //init frame pointer

    //MAIN PIPELINE LOOP
    while(pc != 0x00000000){ //while PC does not jump to 0x000 (end of file);

        ClockCycles++;
        InstructionCount++;

        ///////////////
        //Fetch Stage//
        instFetch();
        ///////////////

        ////////////////
        //Decode Stage//
        IFID = shadow_IFID;
        instDecode();
        ////////////////

        /////////////////
        //Execute Stage//
        IDEX = shadow_IDEX;
        instExecute();
        /////////////////

        ////////////////
        //Memory Stage//
        EXMEM = shadow_EXMEM;
        instMemory();
        ////////////////

        ////////////////////
        //Write Back Stage//
        MEMWB = shadow_MEMWB;
        instWriteBack();
        ////////////////////

    }
    //PRINT OUT FINAL ARRAY VALUES
#ifdef PROGRAM1
    for(int i = 6; i < 10; i++){
        cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
    }
#endif

#ifdef PROGRAM2
    for(int i = 6; i < 10; i++){
        cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
    }
#endif

#ifdef PROGRAMLOADOPT
    for(int i = 795; i < 895; i++){
        cout<<memory[i]<<" "<<memory[i + 100]<<" "<<i<<endl;
    }

    for(int i = 6; i<9; i++){
        cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
    }
#endif

#ifdef PROGRAMLOADUNOPT
    for(int i = 795; i < 895; i++){
        cout<<memory[i]<<" "<<memory[i + 100]<<" "<<i<<endl;
    }

    for(int i = 6; i<9; i++){
        cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
    }
#endif

    cout<<"Instruction Count: "<<InstructionCount<<endl;
    cout<<"Cycle Count: "<<ClockCycles<<endl;
    cout<<"CPI: "<<ClockCycles/InstructionCount<<endl;
    cout<<"i hit rate: "<<ihits*100/iaccesses<<endl;
    cout<<"d hit rate: "<<dhits*100/daccesses<<endl;

    return 1;
}