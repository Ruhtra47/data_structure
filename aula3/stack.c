#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "vector.h"

// typedef struct Stack Stack;
struct Stack
{
    Vector *v;
};

Stack *stack_construct()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->v = vector_construct();

    return s;
}

void stack_destroy(Stack *s)
{
    vector_destroy(s->v);
    free(s);
}

int stack_size(Stack *s)
{
    return vector_size(s->v);
}

void stack_push(Stack *s, void *val)
{
    vector_push_back(s->v, val);
}

void *stack_pop(Stack *s)
{
    return vector_pop_back(s->v);
}