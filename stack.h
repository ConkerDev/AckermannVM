#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "typedefs.h"

struct stack_node {
    struct state data;
    struct stack_node* next;
};

void initStack(struct stack_node* stack);
int isEmpty(struct stack_node *stack);
struct stack_node* pushStack(struct stack_node* stack,struct state data);
struct stack_node* popStack(struct stack_node* stack, struct state* buffer);
