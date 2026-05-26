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

Program *programa_construct(char *name, int prio, int load, int last_use)
{
    Program *p = (Program *)malloc(sizeof(Program));

    strcpy(p->name, name);
    strcpy(p->type, "");
    p->priority = prio;
    p->load = load;
    p->last_use = last_use;
    p->it_begin = -1;

    return p;
}

Program *program_construct_with_type(char *name, char *type, int prio, int load, int it_start)
{
    Program *p = (Program *)malloc(sizeof(Program));

    strcpy(p->name, name);
    strcpy(p->type, type);
    p->priority = prio;
    p->load = load;
    p->last_use = -1;
    p->it_begin = it_start;

    return p;
}

int program_get_priority(Program *p)
{
    return p->priority;
}

int program_get_load(Program *p)
{
    return p->load;
}

int program_get_last_use(Program *p)
{
    return p->last_use;
}

char *program_get_name(Program *p)
{
    return p->name;
}

void program_decrease_load(Program *p)
{
    p->load--;
}

char *program_get_type(Program *p)
{
    return p->type;
}

int program_get_it_begin(Program *p)
{
    return p->it_begin;
}

void program_set_last_use(Program *p, int last_use)
{
    p->last_use = last_use;
}

void program_destroy(Program *p)
{
    free(p);
}