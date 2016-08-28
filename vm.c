#include "vm.h"

void setJumpTags(struct state* state){
	state->jumpTags[0] = 4;
	state->jumpTags[1] = 8;
	state->jumpTags[2] = 13;
	state->jumpTags[3] = 30;
	state->jumpTags[4] = 21;
	state->jumpTags[5] = 26;
	state->jumpTags[6] = 35;
	state->jumpTags[7] = 41;
	state->jumpTags[8] = 49;
	state->jumpTags[9] = 63;
}

void initState(struct state* state){
	setJumpTags(state);
	
	state->returnReg = 0;
	//state->jumpReg = 0;
	state->compbraReg = 0;
	state->instructionPointer = 0;
	state->aReg = 0;
	
	for (int i=0;i<REGISTER_N;i++){
		state->registers[i]=0;
	}
}

void initCPU(struct cpu *cpu) {
	struct state s;
	initState(&s);
	initStack(cpu->stack);

	cpu->state =s;
	//memset(cpu->instructionList,END,sizeof(cpu->instructionList));
	for(int i=0;i<MAXINSTRUCTIONS;i++){
		cpu->instructionList[i] = END;
	}
	/* PROGRAM START */
	
	cpu->instructionList[0]=SET_RET_TO_INPUT;
	cpu->instructionList[1]=COPY_RET_TO_REG_0;
	cpu->instructionList[2]=SET_RET_TO_INPUT;
	cpu->instructionList[3]=COPY_RET_TO_REG_1;
	cpu->instructionList[4]=CHECK_TREE_0_1;		//TAG 0
	cpu->instructionList[5]=COPY_RET_TO_COMPBRA;
	cpu->instructionList[6]=JUMPIFZEROTO1;
	cpu->instructionList[7]=END;
	cpu->instructionList[8]=SET_A_TO_1;			//TAG 1
	cpu->instructionList[9]=INCREMENT_A;
	cpu->instructionList[10]=INCREMENT_A;
	cpu->instructionList[11]=COPY_A_TO_REG_3;
	cpu->instructionList[12]=SET_A_TO_0;
	cpu->instructionList[13]=COPY_REG_0_TO_COMPBRA;		//#TAG 2
	cpu->instructionList[14]=COMPBRA_LARGER_THAN_REG3;
	cpu->instructionList[15]=JUMPIFZEROTO3;
	cpu->instructionList[16]=COPY_REG_1_TO_COMPBRA;
	cpu->instructionList[17]=JUMPIFNOTZEROTO4;
	
	cpu->instructionList[18]=SET_A_TO_1;
	cpu->instructionList[19]=COPY_A_TO_REG_1;
	cpu->instructionList[20]=JUMPTO5;
	cpu->instructionList[21]=COPY_REG_1_TO_A;		//#TAG 4
	cpu->instructionList[22]=DECREMENT_A;
	cpu->instructionList[23]=COPY_A_TO_REG_1;	
	cpu->instructionList[24]=CALL_0;		
	cpu->instructionList[25]=COPY_RET_TO_REG_1;
	cpu->instructionList[26]=COPY_REG_0_TO_A;	//#TAG 5
	cpu->instructionList[27]=DECREMENT_A;
	cpu->instructionList[28]=COPY_A_TO_REG_0;
	
	cpu->instructionList[29]=JUMPTO2;
	cpu->instructionList[30]=COPY_REG_0_TO_COMPBRA;	//TAG 3
	cpu->instructionList[31]=JUMPIFNOTZEROTO6;
	cpu->instructionList[32]=COPY_REG_1_TO_RET;
	cpu->instructionList[33]=INCREMENT_RET;
	cpu->instructionList[34]=JUMPTO9;	
	cpu->instructionList[35]=DECREMENT_COMPBRA;	//#TAG 6	
	cpu->instructionList[36]=JUMPIFNOTZEROTO7;
	cpu->instructionList[37]=COPY_REG_1_TO_RET;
	cpu->instructionList[38]=INCREMENT_RET;
	cpu->instructionList[39]=INCREMENT_RET;
	cpu->instructionList[40]=JUMPTO9;
	
	cpu->instructionList[41]=DECREMENT_COMPBRA;		//#TAG 7
	cpu->instructionList[42]=JUMPIFNOTZEROTO8;	
	cpu->instructionList[43]=SET_A_TO_1;
	cpu->instructionList[44]=INCREMENT_A;
	cpu->instructionList[45]=MULTIPLY_A_REG_1;
	cpu->instructionList[46]=ADD_A_REG_3;	
	cpu->instructionList[47]=COPY_A_TO_RET;
	cpu->instructionList[48]=JUMPTO9;
	cpu->instructionList[49]=DECREMENT_COMPBRA;		//#TAG 8
	cpu->instructionList[50]=JUMPIFNOTZEROTO9;
	cpu->instructionList[51]=COPY_REG_1_TO_A;
	cpu->instructionList[52]=INCREMENT_A;
	cpu->instructionList[53]=INCREMENT_A;
	cpu->instructionList[54]=INCREMENT_A;
	cpu->instructionList[55]=COPY_A_TO_REG_4;
	cpu->instructionList[56]=SET_A_TO_1;
	cpu->instructionList[57]=INCREMENT_A;
	cpu->instructionList[58]=POWER_A_REG_4;
	cpu->instructionList[59]=DECREMENT_A;
	cpu->instructionList[60]=DECREMENT_A;
	cpu->instructionList[61]=DECREMENT_A;
	cpu->instructionList[62]=COPY_A_TO_RET;
	cpu->instructionList[63]=WRITE_TREE_0_1;	//#9
	cpu->instructionList[64]=RETURN;

	/* PROGRAM END */
}

void printRegister(reg_t r){	// MUST BE CHANGED ACORDINGLY WITH THE REG_T
	printf("Register printed: %lld\n",r);
}

void set_ret_to_input(struct state *s){
	char buf[BUFSIZ];
	char *p;
	long long int i;

	printf ("VM PAUSED. REQUEST INPUT: ");
	while(1){
		if (fgets(buf, sizeof(buf), stdin) != NULL){
			i = strtoll(buf, &p, 10);
	
			if (buf[0] != '\n' && (*p == '\n' || *p == '\0')){
				printf ("%lld\n", i);
				s->returnReg = i;
				break;
			}
			else  printf ("Invalid input\n");
		}
	}
}

void printInstruction(enum INSTRUCTION_E instruction){
	printf("Instruction run: ");
	switch (instruction) {
			case END: printf("\n");break;
			
			case SET_RET_1: printf("\n");break;
			case SET_RET_TO_INPUT: printf("\n");break;
			case SET_A_TO_0: printf("\n");break;
			case SET_A_TO_1: printf("\n");break;
			case SET_JUMPR_TO_A: printf("\n");break;
			
			case COPY_RET_TO_REG_0: printf("\n");break;
			case COPY_RET_TO_REG_1:	printf("\n");break;
			case COPY_RET_TO_COMPBRA: printf("\n");break;
			case COPY_A_TO_RET: printf("\n");break;
			case COPY_A_TO_REG_0: printf("\n");break;
			case COPY_A_TO_REG_1: printf("\n");break;
			case COPY_A_TO_REG_3: printf("\n");break;
			case COPY_A_TO_REG_4: printf("\n");break;
			case COPY_REG_1_TO_RET: printf("\n");break;
			case COPY_REG_0_TO_A: printf("\n");break;
			case COPY_REG_1_TO_A: printf("\n");break;
			case COPY_REG_0_TO_COMPBRA: printf("\n");break;
			case COPY_REG_1_TO_COMPBRA: printf("\n");break;
		
			case INCREMENT_A: printf("\n");break;
			case DECREMENT_A: printf("\n");break;
			case ADD_A_REG_3: printf("\n");break;
			case MULTIPLY_A_REG_0: printf("\n");break;
			case MULTIPLY_A_REG_1: printf("\n");break;
			case POWER_A_REG_4: printf("\n");break;
				
			case INCREMENT_RET: printf("\n");break;
			case DECREMENT_RET: printf("\n");break;
			
			case INCREMENT_COMPBRA: printf("\n");break;
			case DECREMENT_COMPBRA: printf("\n");break;
			
			case COMPBRA_LARGER_THAN_REG3: printf("\n");break;			
			
			case JUMPTO2: printf("\n");break;			
			case JUMPTO5: printf("\n");break;
			case JUMPTO9: printf("\n");break;				
			case JUMPIFNOTZEROTO4: printf("\n");break;				
			case JUMPIFNOTZEROTO6: printf("\n");break;				
			case JUMPIFNOTZEROTO7: printf("\n");break;				
			case JUMPIFNOTZEROTO8: printf("\n");break;				
			case JUMPIFNOTZEROTO9: printf("\n");break;				
			case JUMPIFZEROTO1:	printf("\n");break;			
			case JUMPIFZEROTO3:	printf("\n");break;			
			case CALL_0: printf("\n");break;			
			case RETURN: printf("\n");break;			
			case CHECK_TREE_0_1: printf("\n");break;
			case WRITE_TREE_0_1: printf("\n");break;
			case NOP: printf("\n");break;
	}
}
void run(struct cpu *cpu){
	int flag=1;
	while(flag) {
		int autoscrollIP = 1;
		struct state s = cpu->state;
		enum INSTRUCTION_E currentInstruction = cpu->instructionList[s.instructionPointer];
		
		//INSTRUCTION DECODING/EXECUTION
		switch (currentInstruction){
			case END: flag=0; break;
			
			case SET_RET_1: s.returnReg=1; break;
			case SET_RET_TO_INPUT: set_ret_to_input(&s); break;
			case SET_A_TO_0: s.aReg = 0; break;
			case SET_A_TO_1: s.aReg = 1; break;
			case SET_JUMPR_TO_A: /*s.jumpReg = s.aReg; */break;
			
			case COPY_RET_TO_REG_0: s.registers[0] = s.returnReg;break;
			case COPY_RET_TO_REG_1: s.registers[1] = s.returnReg;break;
			case COPY_RET_TO_COMPBRA: s.compbraReg = s.returnReg;break;
			case COPY_A_TO_RET: s.returnReg = s.aReg;break;
			case COPY_A_TO_REG_0: s.registers[0] = s.aReg;break;
			case COPY_A_TO_REG_1: s.registers[1] = s.aReg;break;
			case COPY_A_TO_REG_3: s.registers[3] = s.aReg;break;
			case COPY_A_TO_REG_4: s.registers[4] = s.aReg;break;
			case COPY_REG_1_TO_RET: s.returnReg = s.registers[1];break;
			case COPY_REG_0_TO_A: s.aReg = s.registers[0];break;
			case COPY_REG_1_TO_A: s.aReg = s.registers[1];break;
			case COPY_REG_0_TO_COMPBRA: s.compbraReg = s.registers[0];break;
			case COPY_REG_1_TO_COMPBRA: s.compbraReg = s.registers[0];break;
			
			
			case INCREMENT_A: s.aReg++; break;
			case DECREMENT_A: s.aReg--; break;
			case ADD_A_REG_3: s.aReg = s.aReg + s.registers[3]; break;
			case MULTIPLY_A_REG_0:
				s.aReg = s.aReg * s.registers[0]; break;
			case MULTIPLY_A_REG_1:
				s.aReg = s.aReg * s.registers[1]; break;
			case POWER_A_REG_4:
				s.aReg = pow(s.aReg, s.registers[4]); break;
				
			case INCREMENT_RET: s.returnReg++; break;
			case DECREMENT_RET: s.returnReg--; break;
			
			case INCREMENT_COMPBRA: s.compbraReg++; break;
			case DECREMENT_COMPBRA: s.compbraReg--; break;
			
			case COMPBRA_LARGER_THAN_REG3:								//SETS COMPBRA AS 0 IF FALSE, AS 1 IF TRUE
				if (s.compbraReg > s.registers[3]){
					s.compbraReg = 1;
				} else {
					s.compbraReg = 0;
				} break;
			
			
			
			case JUMPTO2:
				autoscrollIP=0;
				s.instructionPointer = s.jumpTags[2];
				break;
			
			case JUMPTO5:
				autoscrollIP=0;
				s.instructionPointer = s.jumpTags[5];
				break;

				
			case JUMPTO9:
				autoscrollIP=0;
				s.instructionPointer = s.jumpTags[9];
				break;
				
			case JUMPIFNOTZEROTO4: 
				if(s.compbraReg!=0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[4];
				}
				break;
				
			case JUMPIFNOTZEROTO6: 
				if(s.compbraReg!=0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[6];
				}
				break;
				
			case JUMPIFNOTZEROTO7: 
				if(s.compbraReg!=0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[7];
				}
				break;
				
			case JUMPIFNOTZEROTO8: 
				if(s.compbraReg!=0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[8];
				}
				break;
				
			case JUMPIFNOTZEROTO9: 
				if(s.compbraReg!=0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[9];
				}
				break;
				
			case JUMPIFZEROTO1:	
				if(s.compbraReg==0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[1];
				}
				break;
			
			case JUMPIFZEROTO3:	
				if(s.compbraReg==0){
					autoscrollIP=0;	
					s.instructionPointer = s.jumpTags[3];
				}
				break;
			
			case CALL_0:	
				pushStack(cpu->stack,cpu->state);
				autoscrollIP=0;
				s.instructionPointer = s.jumpTags[0];
			break;
			
			case RETURN:	
				if(isEmpty(cpu->stack)){		//Simply end
					flag=0;
				} else {		//return
					struct state tmp;
					cpu->stack = popStack(cpu->stack,&tmp);
					tmp.returnReg = s.returnReg;
					s = tmp;
				}
			break;
			
			case CHECK_TREE_0_1: s.returnReg = 0; break;		//TO IMPLEMENT. SET TO ZERO FORCES RECALC
			case WRITE_TREE_0_1: break;		//TO IMPLEMENT. DOES NOTHING
			case NOP: break;
		}
		if(autoscrollIP)
			s.instructionPointer++;
		cpu->state = s;
	}
	printRegister(cpu->state.returnReg);
}


int main(void) {
	struct cpu* cpu = malloc(sizeof(struct cpu));
	initCPU(cpu);
	run(cpu);

	return EXIT_SUCCESS;
}
