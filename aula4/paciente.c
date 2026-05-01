#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "paciente.h"

struct Paciente
{
    char name[32];
    int age;
};

Paciente *paciente_construct(char *nome, int idade)
{
    Paciente *p = (Paciente *)malloc(sizeof(Paciente));

    strcpy(p->name, nome);
    p->age = idade;

    return p;
}

Paciente *paciente_read()
{
    char nome[32];
    int idade;

    scanf("%s %d", nome, &idade);

    return paciente_construct(nome, idade);
}

int paciente_compare(void *a, void *b)
{
    Paciente *pa = (Paciente *)a;
    Paciente *pb = (Paciente *)b;

    return pa->age - pb->age;
}

void paciente_print(Paciente *p)
{
    printf("%s %d\n", p->name, p->age);
}

void paciente_free(void *p)
{
    free(p);
}