#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"
#include "vector.h"
#include "paciente.h"

int main()
{
    int n;
    scanf("%d", &n);

    Heap *heap = heap_construct(paciente_compare);

    char cmd[10];

    for (int i = 0; i < n; i++)
    {
        scanf("%s", cmd);

        if (!strcmp(cmd, "ADICIONAR"))
        {
            Paciente *p = paciente_read();
            heap_push(heap, p);
        }
        else
        {
            Paciente *val = (Paciente *)heap_pop(heap);
            paciente_print(val);
            paciente_free(val);
        }
    }

    while (!heap_empty(heap))
    {
        Paciente *val = (Paciente *)heap_pop(heap);
        paciente_print(val);
        paciente_free(val);
    }

    heap_destroy(heap, paciente_free);
}