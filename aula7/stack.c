#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "list.h"

// typedef struct Stack
// {
//     List *list;
// } Stack;

Stack *stack_construct()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));

    s->list = list_construct();

    return s;
}

int stack_size(Stack *s)
{
    return list_size(s->list);
}

void stack_push(Stack *s, data_type data)
{
    list_push_front(s->list, data);
}

data_type stack_pop(Stack *s)
{
    return list_pop_front(s->list);
}

void stack_destroy(Stack *s)
{
    list_destroy(s->list);
    free(s);
}