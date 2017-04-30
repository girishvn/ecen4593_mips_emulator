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

        cout<<"Program Counter: "<<pc<<endl;

        ///////////////
        //Fetch Stage//
        instFetch();
        ///////////////

        cout<<"Instruction Fetched: "<<shadow_IFID.mc<<endl;
        cout<<endl;

        IFID = shadow_IFID;

        ////////////////
        //Decode Stage//
        instDecode();
        ////////////////

        cout<<"Decode Stage Finished. Type: "<<shadow_IDEX.type<<endl;
        if(shadow_IDEX.type == N){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
            cout << "Decoding: " << IFID.mc << endl;
            if (shadow_IDEX.type == R) {
                cout<< "R Function: " << +shadow_IDEX.funct
                    << " rd: " << +shadow_IDEX.rd
                    << " rs: " << +shadow_IDEX.rs
                    << " rsVal: " << +shadow_IDEX.rsVal
                    << " rt: " << +shadow_IDEX.rt
                    << " rtVal: " << +shadow_IDEX.rtVal
                    << " shamt: " << +shadow_IDEX.shamt << endl;
            }
            else if (shadow_IDEX.type == I) {
                cout<< "I OP Code: " << +shadow_IDEX.opcode
                    << " rs: " << +shadow_IDEX.rs
                    << " rsVal: " << +shadow_IDEX.rsVal
                    << " rt: " << +shadow_IDEX.rt
                    << " rtVal: " << +shadow_IDEX.rtVal
                    << " Immediate: " << +shadow_IDEX.immediate << endl;
            }
            else if (shadow_IDEX.type == J) {
                cout<< "J OP Code: " << +shadow_IDEX.opcode
                    << " Address: " << +shadow_IDEX.address<< endl;
            }
        }
        cout<<endl;

        IDEX = shadow_IDEX;

        /////////////////
        //Execute Stage//
        instExecute();
        /////////////////

        cout<<"Execute Stage Finished. Type: "<<+shadow_EXMEM.type<<endl;
        if(shadow_EXMEM.nop){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
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
        cout<<endl;

        EXMEM = shadow_EXMEM;

        ////////////////
        //Memory Stage//
        instMemory();
        ////////////////

        cout<<"Memory Stage Finished. Type: "<<shadow_MEMWB.type<<endl;
        if(EXMEM.nop){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
            if (shadow_MEMWB.type == R) {
                cout << "R type doesn't use memory stage. Passed values from EXMEM directly to shadow_MEMWB" << endl
                     << "rv: " << +shadow_MEMWB.rv
                     << " rd: " << +shadow_MEMWB.rd << endl;
            }
            else if (shadow_MEMWB.type == I) {
                if (EXMEM.opcode == 0x24 || EXMEM.opcode == 0x25 || EXMEM.opcode == 0x30 || EXMEM.opcode == 0x23) {
                    cout << "Memory is loaded and being prepared to be written back" << endl
                         << "address: " << +EXMEM.address << endl
                         << "rt: " << +shadow_MEMWB.rt
                         << " rv: " << +shadow_MEMWB.rv
                         << " type: "<< +shadow_MEMWB.type<<endl;

                }
                else if (EXMEM.opcode == 0x28 || EXMEM.opcode == 0x38 || EXMEM.opcode == 0x29 ||
                           EXMEM.opcode == 0x2b) {
                    cout << "Value is written into memory" << endl
                         << "Value: " << memory[EXMEM.address] << endl
                         << "Address: " << EXMEM.address << endl;
                }
                else {
                    cout << "Memory was not accessed" << endl;
                }
            }
            else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode != 0x03) {
                cout << "Jumps are completed before memory stage." << endl;
            }
            //Special case for JAL
            else if(shadow_MEMWB.type == J && shadow_MEMWB.opcode == 0x03){
                cout << "Going to save the return address " << shadow_MEMWB.rv << " into ra." <<endl;
            }
        }
        cout<<endl;

        MEMWB = shadow_MEMWB;

        ////////////////////
        //Write Back Stage//
        ////////////////////
        instWriteBack();
        cout<<"Write Back Stage Finished. Type: "<<shadow_MEMWB.type<<endl;
        if(MEMWB.nop){
            cout<<"Stage Passed, NOP detected or Store instruction was called"<<endl;
        }
        else {
            if (MEMWB.type == I) {
                cout << "Written back: " << MEMWB.rv << " Into register: " << +MEMWB.rt << endl;
            } else if (MEMWB.type == R){
                cout << "Written back: " << MEMWB.rv << " Into register: " << +MEMWB.rd << endl;
            } else if (shadow_MEMWB.type == J && shadow_MEMWB.opcode != 0x03) {
                cout << "Jumps are completed before memory stage." << endl;
            } else if(shadow_MEMWB.type == J && shadow_MEMWB.opcode == 0x03){ //special case for JAL
                cout << "Wrote back the return address value " << MEMWB.rv << " into ra." <<endl;
            }
        }
        cout<<endl;
        MEMWB = shadow_MEMWB;

        //Transferring all shadow registers into normal registers.
        //escapeShadowRealm(); //transfer data from shadow registers to real registers
        //cout<<"All registers have escaped the shadow realm."<<endl;
        cout<<"Instruction has been passed through pipeline."<<endl;
        cout<<"**************************************"<<endl;

    }

    cout<<"Program has finished running"<<endl;

    for(int i = 243; i < 494; i++){ //print out number arra
        cout<<memory[i]<<endl;
    }

    for(int i = 6; i<10; i++){
        cout<<"memory location "<<i<<" = "<<+memory[i]<<endl;
    }


    return 1;
}