#include <iostream>

#include "global_vars.h"
#include "Load_Insts.h"
#include "Fetch.h"
#include "Decode.h"
#include "Execute.h"
#include "Memory.h"
#include "WriteBack.h"

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
    shadow_IDEX.type = 0;
    shadow_IDEX.opcode = 0;
    shadow_IDEX.rd = 32;
    shadow_IDEX.rs = 32;
    shadow_IDEX.rt = 32;
    shadow_IDEX.immediate = 0;
    shadow_IDEX.address = 0;

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

    if(!stall){
        IFID = shadow_IFID;
        pc = pcNext;
        InstructionCount++;
    }
    IDEX = shadow_IDEX;
    EXMEM = shadow_EXMEM;
    MEMWB = shadow_MEMWB;

    //thePurge(); //inits all intermediate register vaues

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
    pc = memory[5]; //set program counter value
    reg[$sp] = memory[0]; //init stack pointer
    reg[$fp] = memory[1]; //init frame pointer

    //MAIN PIPELINE LOOP
    while (pc != 0x00000000) { //while PC does not jump to 0x000 (end of file);
        thePurge();
        cout << "Program Counter: " << pc << endl;

        ///////////////
        //Fetch Stage//
        instFetch();
        ///////////////

        cout << "Instruction Fetched: " << shadow_IFID.mc << endl;
        if (shadow_IFID.type == N) {
            cout << "Stage Passed, NOP detected" << endl;
        } else {
            cout << "Decoding: " << IFID.mc << endl;
            if (shadow_IFID.type == R) {
                cout << "R Function: " << +shadow_IFID.funct
                     << "R OP code: " << +shadow_IFID.opcode
                     << " rd: " << +shadow_IFID.rd
                     << " rs: " << +shadow_IFID.rs
                     << " rt: " << +shadow_IFID.rt
                     << " shamt: " << +shadow_IFID.shamt << endl;
            } else if (shadow_IFID.type == I) {
                cout << "I OP Code: " << +shadow_IFID.opcode
                     << " rs: " << +shadow_IFID.rs
                     << " rt: " << +shadow_IFID.rt << endl;
            } else if (shadow_IFID.type == J) {
                cout << "J OP Code: " << +shadow_IFID.opcode << endl;
            }
        }
        cout << endl;

        ////////////////////
        //Write Back Stage//
        //MEMWB = shadow_MEMWB;
        instWriteBack();
        ////////////////////


        cout << "Write Back Stage Finished. Type: " << shadow_MEMWB.type << endl;
        if (MEMWB.nop) {
            cout << "Stage Passed, NOP detected or Store instruction was called" << endl;
        } else {
            if (MEMWB.type == I) {
                cout << "Written back: " << MEMWB.rv << " Into register: " << +MEMWB.rt << endl;
            } else if (MEMWB.type == R) {
                cout << "Written back: " << MEMWB.rv << " Into register: " << +MEMWB.rd << endl;
            } else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode != 0x03) {
                cout << "Jumps are completed before memory stage." << endl;
            } else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode == 0x03) { //special case for JAL
                cout << "Wrote back the return address value " << MEMWB.rv << " into ra." << endl;
            }
        }
        cout << endl;

        ////////////////
        //Decode Stage//
        //IFID = shadow_IFID;
        instDecode();
        ////////////////

        cout << "Decode Stage Finished. Type: " << shadow_IDEX.type << endl;
        if (shadow_IDEX.type == N) {
            cout << "Stage Passed, NOP detected" << endl;
        } else {
            cout << "Decoding: " << IFID.mc << endl;
            if (shadow_IDEX.type == R) {
                cout << "R Function: " << +shadow_IDEX.funct
                     << " rsVal: " << +shadow_IDEX.rsVal
                     << " rtVal: " << +shadow_IDEX.rtVal
                     << " shamt: " << +shadow_IDEX.shamt << endl;
            } else if (shadow_IDEX.type == I) {
                cout << "I OP Code: " << +shadow_IDEX.opcode
                     << " rsVal: " << +shadow_IDEX.rsVal
                     << " rtVal: " << +shadow_IDEX.rtVal
                     << " Immediate: " << +shadow_IDEX.immediate << endl;
            } else if (shadow_IDEX.type == J) {
                cout << "J OP Code: " << +shadow_IDEX.opcode
                     << " Address: " << +shadow_IDEX.address << endl;
            }
        }
        cout << endl;

        /////////////////
        //Execute Stage//
        //IDEX = shadow_IDEX;
        instExecute();
        /////////////////


        cout << "Execute Stage Finished. Type: " << +shadow_EXMEM.type << endl;
        if (shadow_EXMEM.nop) {
            cout << "Stage Passed, NOP detected" << endl;
        } else {
            if (shadow_EXMEM.type == R) {
                cout << "R Function " << +shadow_EXMEM.funct
                     << " rd " << +shadow_EXMEM.rd
                     << " rs " << +shadow_EXMEM.rs
                     << " rsVal " << +shadow_EXMEM.rsVal
                     << " rt " << +shadow_EXMEM.rt
                     << " rtVal " << +shadow_EXMEM.rtVal
                     << " shamt " << +shadow_EXMEM.shamt
                     << " rv " << +shadow_EXMEM.rv << endl;
            } else if (shadow_EXMEM.type == I) {
                cout << "I OP Code: " << +shadow_EXMEM.opcode
                     << " immediate: " << +IDEX.immediate
                     << " rs: " << +shadow_EXMEM.rs
                     << " rsVal " << +shadow_EXMEM.rsVal
                     << " rt: " << +shadow_EXMEM.rt
                     << " rtVal " << +shadow_EXMEM.rtVal
                     << " rv: " << +shadow_EXMEM.rv
                     << " address: " << +shadow_EXMEM.address << endl;
            } else if (shadow_EXMEM.type == J && shadow_EXMEM.opcode != 0x02) {
                cout << "J OP Code: " << +shadow_EXMEM.opcode << endl
                     << "New PC address calculated is: " << pc << endl;
            } else if (shadow_EXMEM.type == J && shadow_EXMEM.opcode == 0x03) {
                cout << "J OP Code: " << +shadow_EXMEM.opcode << endl
                     << "New PC address calculated is: " << pc << endl
                     << "Calculated return address to store in ra: " << shadow_MEMWB.rv << endl;
            }
        }
        cout << endl;


        ////////////////
        //Memory Stage//
        //EXMEM = shadow_EXMEM;
        instMemory();
        ////////////////


        cout << "Memory Stage Finished. Type: " << shadow_MEMWB.type << endl;
        if (EXMEM.nop) {
            cout << "Stage Passed, NOP detected" << endl;
        } else {
            if (shadow_MEMWB.type == R) {
                cout << "R type doesn't use memory stage. Passed values from EXMEM directly to shadow_MEMWB" << endl
                     << "rv: " << +shadow_MEMWB.rv
                     << " rd: " << +shadow_MEMWB.rd << endl;
            } else if (shadow_MEMWB.type == I) {
                if (EXMEM.opcode == 0x24 || EXMEM.opcode == 0x25 || EXMEM.opcode == 0x30 || EXMEM.opcode == 0x23) {
                    cout << "Memory is loaded and being prepared to be written back" << endl
                         << "address: " << +EXMEM.address << endl
                         << "rt: " << +shadow_MEMWB.rt
                         << " rv: " << +shadow_MEMWB.rv
                         << " type: " << +shadow_MEMWB.type << endl;

                } else if (EXMEM.opcode == 0x28 || EXMEM.opcode == 0x38 || EXMEM.opcode == 0x29 ||
                           EXMEM.opcode == 0x2b) {
                    cout << "Value is written into memory" << endl
                         << "Value: " << memory[EXMEM.address] << endl
                         << "Address: " << EXMEM.address << endl;
                } else {
                    cout << "Memory was not accessed" << endl;
                }
            } else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode != 0x03) {
                cout << "Jumps are completed before memory stage." << endl;
            }
                //Special case for JAL
            else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode == 0x03) {
                cout << "Going to save the return address " << shadow_MEMWB.rv << " into ra." << endl;
            }
        }
        cout << endl;

        //Transferring all shadow registers into normal registers.
        escapeShadowRealm(); //transfer data from shadow registers to real registers
        cout<<"All registers have escaped the shadow realm."<<endl;
        ClockCycles++;
        //cout << "Instruction has been passed through pipeline." << endl;
        //cout << "**************************************" << endl;
    }
        //PRINT OUT FINAL ARRAY VALUES
#ifdef PROGRAM1
        for(int i = 243; i < 493; i++){
            cout<<memory[i]<<" "<<memory[i + 250]<<" "<<i<<endl;
        }

        for(int i = 6; i < 10; i++){
            cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
        }
#endif

#ifdef PROGRAM2
        for (int i = 395; i < 495; i++) {
            cout << memory[i] << " " << i << endl;
        }
        for (int i = 6; i < 10; i++) {
            cout << "memory location " << i << " = " << +memory[i] << endl;
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
        cout << "Program has finished running" << endl;
        return 1;
}