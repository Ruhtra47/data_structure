#ifndef _PROGRAMA_H
#define _PROGRAMA_H

typedef struct Program Program;

Program *programa_construct(char *name, int prio, int load, int last_use);
Program *program_construct_with_type(char *name, char *type, int prio, int load, int it_start);
void program_decrease_load(Program *p);
int program_get_priority(Program *p);
int program_get_load(Program *p);
char *program_get_name(Program *p);
int program_get_last_use(Program *p);
char *program_get_type(Program *p);
int program_get_it_begin(Program *p);
void program_set_last_use(Program *p, int last_use);
void program_destroy(Program *p);

#endif