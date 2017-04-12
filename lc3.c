#include "lc3.h"
#include <stdio.h> 
#include <stdlib.h>

/*Phansa Chaonpoj
Samantha Shoecraft
problem 2
lc3.c - implement the instructions add, and, not, trap, ld, st,
jmp, and br as a lc3 simulator.
*/

// you can define a simple memory module here for this program
unsigned short memory[32];   // 32 words of memory enough to store simple program



int main(int argc, char* argv[]) {
//making change to code test
short int com_in;
if (argc > 1){
	sscanf(argv[1],"%hX", &com_in);//takes command from command line
 	struct cpu_s cpu1;//creating cpu
 	CPU_p cpu = &cpu1;//creating pointer to cpu
 	cpu->pc =0;
 	memory[0] = com_in;
 	controller(cpu);
}
}
int controller (CPU_p cpu) 
{
    // check to make sure both pointers are not NULL
	if (cpu == NULL){
		return 1;
	}
    // do any initializations here
	unsigned int opcode, state, Rd, Rs1, Rs2, immed;	// fields for the IR
    state = FETCH;
    for (;;) {   // efficient endless loop
        switch (state) {
            case FETCH: // microstates 18, 33, 35 in the book
                printf("Here in FETCH\n");

                //moving memory at pc into instruction register
                cpu->ir = memory[cpu->pc];

                // get memory[PC] into IR - memory is a global array
                // increment PC
                printf("Contents of IR = %04X\n", cpu->ir);
				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                // put printf statements in each state and microstate to see that it is working
 				//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
               state = DECODE;
                break;
            case DECODE: // microstate 32
                // get the fields out of the IR
                printf("Im in decode ");
                opcode = (cpu->ir >> OPP_LSB) & ~(~0 << (OPP_MSB-OPP_LSB+1));//for instruction 
                
                //destination register
                Rd= (cpu->ir >> DR_LSB) & ~(~0 << (DR_MSB-DR_LSB+1));

                //first source register
                Rs1= (cpu->ir >> SR_LSB) & ~(~0 << (SR_MSB-SR_LSB+1));
                //second source register
                Rs2= (cpu->ir >> SR2_LSB) & ~(~0 << (SR2_MSB-SR2_LSB+1));
                immed =  (cpu->ir >> IMMED_LSB) & ~(~0 << (IMMED_MSB-IMMED_LSB+1));
                // make sure opcode is in integer form
				// hint: use four unsigned int variables, opcode, Rd, Rs, and immed7
				// extract the bit fields from the IR into these variables
                state = EVAL_ADDR;
                break;
            case EVAL_ADDR: // Look at the LD instruction to see microstate 2 example
                switch (opcode) {
                // different opcodes require different handling
                // compute effective address, e.g. add sext(immed7) to register
			case ADD:
			break;
			case AND:
			break;
			case NOT:
			break;
			case TRAP:
			break;
			case LD:
			break;
			case ST:
			break;
			case JMP:
			break;
			case BR:
			break;
			default:
			break;
                }
                state = FETCH_OP;
                break;
            case FETCH_OP: // Look at ST. Microstate 23 example of getting a value out of a register
                switch (opcode) {
                    // get operands out of registers into A, B of ALU
                    // or get memory for load instr.
			case ADD:
			break;
			case AND:
			break;
			case NOT:
			break;
			case TRAP:
			break;
			case LD:
			break;
			case ST:
			break;
			case JMP:
			break;
			case BR:
			break;
			default:
			break;
                }
                state = EXECUTE;
                break;
            case EXECUTE: // Note that ST does not have an execute microstate
                switch (opcode) {
                    // do what the opcode is for, e.g. ADD
                    // in case of TRAP: call trap(int trap_vector) routine, see below for TRAP x25 (HALT)
			case ADD:
			break;
			case AND:
			break;
			case NOT:
			break;
			case TRAP:
			break;
			case LD:
			break;
			case ST:
			break;
			case JMP:
			break;
			case BR:
			break;
			default:
			break;
                }
                state = STORE;
                break;
            case STORE: // Look at ST. Microstate 16 is the store to memory
                switch (opcode) {
                    // write back to register or store MDR into memory
			case ADD:
			break;
			case AND:
			break;
			case NOT:
			break;
			case TRAP:
			break;
			case LD:
			break;
			case ST:
			break;
			case JMP:
			break;
			case BR:
			break;
			default:
			break;
                }

                // do any clean up here in prep for the next complete cycle
                state = FETCH;
		return 0;
                break;
	
        }
    }
}
