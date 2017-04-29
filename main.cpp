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

    pc = memory[0]; //set program counter value
    //reg[$sp] = memory[0]; //init stack pointer
    //reg[$fp] = memory[1]; //init frame pointer


    while(pc != 12){ //while PC does not jump to 0x000 (end of file)

        ///////////////
        //Fetch Stage//
        ///////////////
        instFetch();
        cout<<"Program Counter value: "<<pc<<endl
            <<"Instruction Fetched: "<<shadow_IFID.mc<<endl;
        cout<<endl;

        ////////////////
        //Decode Stage//
        ////////////////
        instDecode();
        cout<<"Decode Stage Finished. Type: "<<shadow_IDEX.type<<endl;
        if(shadow_IDEX.nop){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
            cout << "Decoding: " << IFID.mc << endl;
            if (shadow_IDEX.type == R) {
                cout << "rd: " << +shadow_IDEX.rd << endl
                     << "rs: " << +shadow_IDEX.rs << endl
                     << "rt: " << +shadow_IDEX.rt << endl
                     << "shamt: " << +shadow_IDEX.shamt << endl
                     << "funct: " << +shadow_IDEX.funct << endl;
            } else if (shadow_IDEX.type == I) {
                cout << "rs: " << +shadow_IDEX.rs << endl
                     << "rt: " << +shadow_IDEX.rt << endl
                     << "Immediate: " << +shadow_IDEX.immediate << endl;
            } else if (shadow_IDEX.type == J) {
                cout << "Address: " << +shadow_IDEX.address << endl;
            }
        }
        cout<<endl;

        /////////////////
        //Execute Stage//
        /////////////////
        instExecute();
        cout<<"Execute Stage Finished. Type: "<<+shadow_EXMEM.type<<endl;
        if(IDEX.nop == true){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
            if (shadow_EXMEM.type == R) {
                cout << "Function " << +shadow_EXMEM.funct << endl
                     << "rs " << +shadow_EXMEM.rs << endl
                     << "rt " << +shadow_EXMEM.rt << endl
                     << "rd " << +shadow_EXMEM.rd << endl
                     << "shamt " << +shadow_EXMEM.shamt << endl
                     << "rv " << +shadow_EXMEM.rv << endl;
            } else if (shadow_EXMEM.type == I) {
                cout << "opcode: " << +shadow_EXMEM.opcode << endl
                     << "immediate: " << +shadow_EXMEM.immediate << endl
                     << "rt: " << +shadow_EXMEM.rt << endl
                     << "rs: " << +shadow_EXMEM.rs << endl
                     << "rv: " << +shadow_EXMEM.rv << endl
                     << "address: "<< +shadow_EXMEM.address << endl;
            } else if (shadow_EXMEM.type == J) {
                cout << "Jumps Are completed by Memory stage." << endl;
            }
        }
        cout<<endl;

        ////////////////
        //Memory Stage//
        ////////////////
        instMemory();
        cout<<"Memory Stage Finished. Type: "<<shadow_MEMWB.type<<endl;
        if(EXMEM.nop == true){
            cout<<"Stage Passed, NOP detected"<<endl;
        }
        else {
            if (shadow_MEMWB.type == R) {
                cout << "R type doesn't use memory stage. Passed values from EXMEM directly to shadow_MEMWB" << endl
                     << "rv: " << +shadow_MEMWB.rv << endl
                     << "rd: " << +shadow_MEMWB.rd << endl;
            } else if (shadow_MEMWB.type == I) {
                if (EXMEM.opcode == 0x24 || EXMEM.opcode == 0x25 || EXMEM.opcode == 0x30 || EXMEM.opcode == 0x23) {
                    cout << "Memory is loaded and being prepared to be written back" << endl
                         << "rv: " << +shadow_MEMWB.rv << endl
                         << "rt: " << +shadow_MEMWB.rt << endl;

                } else if (EXMEM.opcode == 0x28 || EXMEM.opcode == 0x38 || EXMEM.opcode == 0x29 ||
                           EXMEM.opcode == 0x2b) {
                    cout << "Value is being written into memory" << endl
                         << "rv: " << EXMEM.rv << endl
                         << "Address: " << EXMEM.address << endl;
                } else {
                    cout << "Memory was not accessed" << endl;
                }
            } else if (shadow_MEMWB.type == J) {
                cout << "Jumps are completed by memory stage." << endl;
            }
        }
        cout<<endl;

        ////////////////////
        //Write Back Stage//
        ////////////////////
        instWriteBack();
        cout<<"Write Back Stage Finished. Type: "<<shadow_MEMWB.type<<endl;
        if(MEMWB.nop == true){
            cout<<"Stage Passed, NOP detected or Store instruction was called"<<endl;
        }
        else {
            if (MEMWB.type == R || MEMWB.type == I) {
                cout << "Written back: " << MEMWB.rv << " Into register: " << +MEMWB.rt << endl;
            } else if (shadow_EXMEM.type == J) {
                cout << "Jumps Are completed by Write Back stage." << endl;
            }
        }
        cout<<endl;

        //Transferring all shadow registers into normal registers.
        escapeShadowRealm(); //transfer data from shadow registers to real registers
        cout<<"All registers have escaped the shadow realm."<<endl;
        cout<<"**************************************"<<endl;

        cout<<int(reg[9])<<" "<<int(reg[10])<<" "<<reg[11]<<" "<<memory[17]<<endl;
    }
    cout<<int(reg[9])<<" "<<int(reg[10])<<" "<<reg[11]<<" "<<memory[17]<<endl;
    cout<<"Program has finished running"<<endl;

/***********************************************************************************************************************

TEST CODE

***********************************************************************************************************************/
/*
    uint32_t mc = 0x00ff2244; //test machine code
    IFID.mc = mc;

    instDecode(); //calling ID stage of pipeline

    std::cout <<"type: "<<IDEX.type<< std::endl;
    std::cout <<"rd: "<<int(IDEX.rd)<< std::endl;
    std::cout <<"rs: "<<int(IDEX.rs)<< std::endl;
    std::cout <<"rt: "<<int(IDEX.rt)<< std::endl;


    uint16_t tst = 0xffaa;
    int16_t signedtst = int16_t(tst);

    std::cout <<"unsigned 16 bit val: "<<int(IDEX.rs)<< std::endl;
    std::cout <<"2signed 16 bit val: "<<int(IDEX.rt)<< std::endl;
*/
    return 1;

}