#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "vector.h"
#include "processo.h"
#include "priority_queu_vector.h"

int main()
{
    int n;
    scanf("%d", &n);

    // Heap *heap = heap_construct(processo_compare);
    PriorityQueue *pq = pq_constructor(processo_compare);

    for (int i = 0; i < n; i++)
    {
        Processo *p = processo_read();
        // heap_push(heap, p);
        pq_push(pq, p);
    }

    for (int i = 0; i < n; i++)
    {
        // Processo *val = (Processo *)heap_pop(heap);
        Processo *val = (Processo *)pq_pop(pq);
        processo_print(val);
        processo_free(val);
    }

    // heap_destroy(heap, processo_free);
    pq_destroy(pq, processo_free);
}