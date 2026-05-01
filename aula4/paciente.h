#ifndef _PACIENTE_H
#define _PACIENTE_H

typedef struct Paciente Paciente;

Paciente *paciente_construct(char *nome, int idade);
Paciente *paciente_read();
int paciente_compare(void *a, void *b);
void paciente_print(Paciente *a);
void paciente_free(void *p);

#endif