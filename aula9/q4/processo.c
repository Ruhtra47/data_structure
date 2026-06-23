#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processo.h"

typedef struct Processo
{
    char nome[32];
    char categoria[32];
    int id;
    int priority;
} Processo;

Processo *processo_construct(char *nome, char *categoria, int id, int priority)
{
    Processo *p = (Processo *)malloc(sizeof(Processo));

    strcpy(p->nome, nome);
    strcpy(p->categoria, categoria);
    p->id = id;
    p->priority = priority;

    return p;
}

Processo *processo_read()
{
    char nome[32], cat[32];
    int id, priority;

    scanf("%s %s %d %d\n", nome, cat, &id, &priority);
    return processo_construct(nome, cat, id, priority);
}

int processo_compare(void *a, void *b)
{
    if (a == 0 || b == 0)
    {
        return 1;
    }

    Processo *pa = (Processo *)a;
    Processo *pb = (Processo *)b;

    return pa->priority - pb->priority;
}

void processo_print(void *val)
{
    Processo *p = (Processo *)val;
    printf("%s %s %d %d\n", p->nome, p->categoria, p->id, p->priority);
}

void processo_free(void *val)
{
    free(val);
}