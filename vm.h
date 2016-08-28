#include <stdio.h>
#include <string.h>
#include <math.h>

#include "typedefs.h"
#include "stack.h"

#define MAXINSTRUCTIONS 65

struct cpu {
	struct state state;
	enum INSTRUCTION_E instructionList[MAXINSTRUCTIONS];
	struct stack_node * stack;
};

void initState(struct state* state);
void initCPU(struct cpu *cpu);
void run(struct cpu *cpu);
void printRegister(reg_t r);	// MUST BE CHANGED ACORDINGLY WITH THE REG_T
