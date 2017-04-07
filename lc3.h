#define CPU_H
#define FETCH 0
#define DECODE 1
#define EVAL_ADDR 2
#define FETCH_OP 3
#define EXECUTE 4
#define STORE 5

#define OPP_LSB 12
#define OPP_MSB 15
#define DR_LSB 11
#define DR_MSB 9
#define SR_LSB 6
#define SR_MSB 8
#define SR2_LSB 0
#define SR2_MSB 2
#define IMMED_LSB 0
#define IMMED_MSB 4



#define ADD 0
#define AND 1
#define NOT 2
#define TRAP 3
#define LD 4
#define ST 5
#define JMP 6
#define BR 7


typedef unsigned short Register;


typedef struct cpu_s {
    Register reg[8];
    int pc; 
    Register ir;
    Register MAR;
    Register MDR;
     
} CPU_S; 

typedef struct cpu_s* CPU_p; 
