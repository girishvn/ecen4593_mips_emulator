#include <iostream>

#include "_decode.h"

using namespace std;

//Global Variables:

uint32_t register_bank[32]; //32-register system
uint32_t programCount; //program counter


int main() {

    uint32_t mc = 0x00ff2244; //test machine code
    instruction inst;


    instDecode(mc, &inst); //calling ID stage of pipeline

    std::cout <<"type: "<<inst.type<< std::endl;
    std::cout <<"rd: "<<int(inst.rd)<< std::endl;
    std::cout <<"rs: "<<int(inst.rs)<< std::endl;
    std::cout <<"rt: "<<int(inst.rt)<< std::endl;

    return 0;

}