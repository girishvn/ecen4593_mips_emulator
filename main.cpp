#include <iostream>

#include "global_vars.h"
#include "decode.h"


using namespace std;



int main() {

    uint32_t mc = 0x00ff2244; //test machine code

    instDecode(mc); //calling ID stage of pipeline

    std::cout <<"type: "<<IDEX.type<< std::endl;
    std::cout <<"rd: "<<int(IDEX.rd)<< std::endl;
    std::cout <<"rs: "<<int(IDEX.rs)<< std::endl;
    std::cout <<"rt: "<<int(IDEX.rt)<< std::endl;

    return 0;

}