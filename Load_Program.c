/* Porting example code to test */
#include "Load_Program.h"
//#include "testbench.h" //Girish comment

unsigned int memory[memory_size]; //global array memory

/***********************************************************************************************************************

 FUNCTION NAME: Initialize_Simulation_Memory

 DESCRIPTION: Copies instruction machine code from program image to memory array (Adapted from Professor Graham's code)

 INPUTS: void

 OUTPUTS: void

***********************************************************************************************************************/

void Initialize_Simulation_Memory(void){

	for (int i=0; i < memory_size; i++){

		memory[i] = program_image[i];

	}
}
