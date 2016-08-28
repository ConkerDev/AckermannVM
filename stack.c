#include "stack.h"

void initStack(struct stack_node* stack) {
	stack = NULL;
}

int isEmpty(struct stack_node *stack){
    return (stack == NULL) ? 1 : 0;
}

struct stack_node* pushStack(struct stack_node* stack,struct state data) {
    struct stack_node* tmp = malloc(sizeof(struct stack_node));
    if(tmp == NULL) {
		printf("FATAL ERROR: MEMORY FULL\n");
        exit(0);
    }
    tmp->data = data;
    tmp->next = stack;
    stack = tmp;
    return stack;
}

struct stack_node* popStack(struct stack_node *stack,struct state *buffer){
    struct stack_node* tmp = stack;
    *buffer = stack->data;
    stack = stack->next;
    free(tmp);
    return stack;
}

