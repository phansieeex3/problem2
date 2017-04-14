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

//changes data, passed in by reference.
void aluFunction(int opcode, ALU_p alu);

int main(int argc, char* argv[]) {
//making change to code test
short int com_in;
if (argc > 1){
	sscanf(argv[1],"%hX", &com_in);//takes command from command line
 	struct cpu_s cpu1;//creating cpu
 	CPU_p cpu = &cpu1;//creating pointer to cpu
 	cpu->pc =0;
 	memory[0] = com_in;
	cpu->reg[1] = FIVE;
	cpu->reg[2] = FIVETEEN;
	cpu->reg[3] = ZERO;
 	controller(cpu);
}
}
int controller (CPU_p cpu) 
{
    struct alu_s alus;
    ALU_p alu = &alus;

    // check to make sure both pointers are not NULL
	if (cpu == NULL || memory == NULL){
		return 1;
	}
    // do any initializations here
	unsigned int opcode, state, Rd, Rs1, Rs2, immed, immed7, PCoff9;	// fields for the IR
    state = FETCH;
    for (;;) {   // efficient endless loop
        switch (state) 
		{
            case FETCH: // microstates 18, 33, 35 in the book
                printf("Here in FETCH\n");
		cpu->MAR = cpu->pc;//ms 18
                //moving memory at pc into instruction register 33
                cpu->MDR = memory[cpu->pc];
		R=1;
                // get memory[PC] into IR - memory is a global array
		cpu->ir = memory[cpu->pc];
                // increment PC- ms 18
		if (cpu->pc < 31)
		{
		cpu->pc ++;
		} else 
		{
		cpu->pc = 0;
		}
		printf("Microstate 18, MAR is %d pc is now : %d", cpu->MAR, cpu->pc);
		printf("\nMicrostate 33, MDR is 0X%hX", cpu->MDR);
		
                printf("\nMicroState 35, Contents of IR = %04X\n", cpu->ir);
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
		//printf("\nDestination register is: %d", Rd);
                //first source register /baseR
                Rs1= (cpu->ir >> SR_LSB) & ~(~0 << (SR_MSB-SR_LSB+1));
		printf("\nSource register 1 is : %d", Rs1);
                //second source register
                Rs2= (cpu->ir >> SR2_LSB) & ~(~0 << (SR2_MSB-SR2_LSB+1));
		//printf("\nSource register 2 is : %d", Rs2);
		PCoff9 = (cpu->ir >> 0) & ~(~0 << (8-0 +1));
		//printf("\n PCoff9 is : %d", PCoff9);
                immed =  (cpu->ir >> IMMED_LSB) & ~(~0 << (IMMED_MSB-IMMED_LSB+1));
		immed7 = (cpu->ir >> 0) & ~(~0 << (7-0+1));
		//printf("\nimmed is : %d", immed);
		CC = (cpu->ir >> 5) & ~(~0 << (5-5 +1));
                // make sure opcode is in integer form
		BEN = ((cpu->ir >> 11) & ~(~0 << (11-11+1)) && N) + ((cpu->ir >> 10) & ~(~0 << (10-10+1)) && Z) +((cpu->ir >> 9) & ~(~0 << (9-9+1)) && P);
		printf("\nMicrostate 32, BEN is :%d Opcode is : %d\n", BEN, opcode);
				// hint: use four unsigned int variables, opcode, Rd, Rs, and immed7
				// extract the bit fields from the IR into these variables
                state = EVAL_ADDR;
                break;
            case EVAL_ADDR: // Look at the LD instruction to see microstate 2 example
		printf("I'm evaluating the address");
                switch (opcode) {
                // different opcodes require different handling
                // compute effective address, e.g. add sext(immed7) to register
			case ADD:
				
					break;  
			case AND:
			
					break;
			case NOT:
			
					break;
			case TRAP://15
				cpu->MAR = (immed7 & cpu->reg[2]);
                        	printf("Microstate 15 Trap,MAR : = %hX", cpu->MAR);
					break;
			case LD:
					cpu->MAR = cpu->pc + PCoff9;
			break;
			case ST:
					cpu->MAR = cpu->pc + PCoff9;
					break;
			case JMP:
					cpu->pc = cpu->reg[Rs1];
					break;
			case BR:
					cpu->pc += PCoff9;
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
					alu->a = cpu->reg[Rs1];
					if(CC)
					{
						alu->b = immed;
					}
					else{
						alu->b = cpu->reg[Rs2];
					}
			break;
					case AND:
					alu->a = cpu->reg[Rs1];
					if(CC)
					{
						alu->b = immed;
					}
					else
					{
						alu->b = cpu->reg[Rs2];
					}
					break;
			case NOT:
					alu->a = cpu->reg[Rs1];
					alu->b = 0;
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
		     	aluFunction(ADD, alu); //passing in the pointer of alu to do the add op
			break;
			case AND:
				//passing in the pointer of alu to do the and operation .
				aluFunction(AND, alu); 
			break;
			case NOT:
			//passing in the pointer of alu to do the not operation .
				aluFunction(NOT, alu);

			break;
			case TRAP: //the rest of the functions should be empty. 
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

/* Passed in by reference of alu. */
void aluFunction(int opcode, ALU_p alu){

	if(opcode == ADD)
	{
		alu->r = alu->a + alu->b ;
	}
	else if(opcode == AND)
	{
		//temp for bit shifting 
		alu->r = alu->a&alu->b; 

	}
	else if(opcode == NOT)
	{
		alu->r = ~(alu->a);

		//if it's in register b then use this '
		//alu->r = ~(alu->b);
	}


}
