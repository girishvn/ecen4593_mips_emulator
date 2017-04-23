/* Porting example code to test */
#include "Load_Program.h"
//#include "testbench.h" //Girish comment

unsigned int memory[memory_size];

void Initialize_Simulation_Memory(void){

	for (int i=0; i < memory_size; i++){

		memory[i] = program_image[i];

	}
}
