#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "vector.h"
#include "processo.h"

int main()
{
    int n;
    scanf("%d", &n);

    Heap *heap = heap_construct(processo_compare);

    for (int i = 0; i < n; i++)
    {
        Processo *p = processo_read();
        heap_push(heap, p);
    }

    for (int i = 0; i < n; i++)
    {
        Processo *val = (Processo *)heap_pop(heap);
        processo_print(val);
        processo_free(val);
    }

    heap_destroy(heap, processo_free);
}