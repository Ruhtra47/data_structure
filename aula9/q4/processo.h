#ifndef _PROCESSO_H
#define _PROCESSO_H

typedef struct Processo Processo;

Processo *processo_construct(char *nome, char *categoria, int id, int priority);
Processo *processo_read();
int processo_compare(void *a, void *b);
void processo_print(void *val);
void processo_free(void *val);

#endif