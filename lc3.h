/*Phansa Chaonpoj
Samantha Shoecraft
problem 2
lc3.c - implement the instructions add, and, not, trap, ld, st,
jmp, and br as a lc3 simulator.
*/
#define CPU_H
#define FETCH 0
#define DECODE 1
#define EVAL_ADDR 2
#define FETCH_OP 3
#define EXECUTE 4
#define STORE 5

#define OPP_LSB 12
#define OPP_MSB 15
#define DR_LSB 9
#define DR_MSB 11
#define SR_LSB 6
#define SR_MSB 8
#define SR2_LSB 0
#define SR2_MSB 2
#define IMMED_LSB 0
#define IMMED_MSB 4

#define FIVE 0x0005
#define FIVETEEN 0x000F
#define ZERO 0x0000
#define ADD 1
#define AND 5
#define NOT 9
#define TRAP 15
#define LD 2
#define ST 3
#define JMP 12
#define BR 0
#define ALU_ADD 0
#define ALU_AND 1
#define ALU_NOT 2

typedef unsigned short Register;
typedef unsigned char Bit;
Bit BEN=0;
Bit N =0;
Bit Z = 0;
Bit P = 0;
Bit CC =0;
typedef struct cpu_s {
    Register reg[8];
    int pc; 
    Register ir;
    Register MAR;
    Register MDR;
     
} CPU_S; 
typedef struct alu_s {
   Register a;
   Register b;
   Register r;
}ALU_S;
typedef struct alu_s* ALU_p;
typedef struct cpu_s* CPU_p; 
int controller (CPU_p cpu);
void aluFunction(int opcode, ALU_p alu);
void setCC(int result);
