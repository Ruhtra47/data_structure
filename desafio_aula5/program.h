#ifndef _PROGRAMA_H
#define _PROGRAMA_H

typedef struct Program Program;

Program *programa_construct(char *name, char *type, int prio, int load, int last_use);

#endif