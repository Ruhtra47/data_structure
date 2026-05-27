#ifndef _STACK_H
#define _STACK_H

#include "list.h"

typedef struct Stack
{
    List *list;
} Stack;

Stack *stack_construct();
int stack_size(Stack *s);
void stack_push(Stack *s, data_type data);
data_type stack_pop(Stack *s);
void stack_destroy(Stack *s);

#endif