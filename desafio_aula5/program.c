#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"

// typedef struct Programa Programa;
struct Program
{
    char name[64];
    char type[5];
    int priority;
    int load;
    int last_use;
    int it_begin;
};

Program *programa_construct(char *name, char *type, int prio, int load, int last_use)
{
    Program *p = (Program *)malloc(sizeof(Program));

    strcpy(p->name, name);
    strcpy(p->type, type);
    p->priority = prio;
    p->load = load;
    p->last_use = last_use;
    p->it_begin = -1;

    return p;
}

void program_decrease_load(Program *p)
{
    p->load--;
}

void program_destroy(Program *p)
{
    free(p);
}