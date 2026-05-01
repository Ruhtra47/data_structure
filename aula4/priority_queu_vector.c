#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "priority_queu_vector.h"

// typedef struct PriorityQueue PriorityQueue;
struct PriorityQueue
{
    Vector *data;
    compare_fn cmp;
};

PriorityQueue *pq_constructor(compare_fn cmp_fn)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

    pq->data = vector_construct();
    pq->cmp = cmp_fn;

    return pq;
}

void pq_push(PriorityQueue *pq, void *data)
{
    for (int i = 0; i < vector_size(pq->data); i++)
    {
        if (pq->cmp(data, vector_get(pq->data, i)) > 0)
        {
            vector_insert(pq->data, i, data);
            return;
        }
    }

    vector_insert(pq->data, vector_size(pq->data), data);
}

void *pq_pop(PriorityQueue *pq)
{
    void *removed = vector_remove(pq->data, 0);

    return removed;
}

int pq_size(PriorityQueue *pq)
{
    return vector_size(pq->data);
}

void pq_destroy(PriorityQueue *pq, void (*free_item)(void *))
{
    for (int i = 0; i < pq_size(pq); i++)
    {
        free_item(vector_get(pq->data, i));
    }
    vector_destroy(pq->data);
    free(pq);
}