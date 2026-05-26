#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "priority_queue.h"

#define INITIAL_CAP 20

// typedef struct PriorityQueue PriorityQueue;
struct PriorityQueue
{
    int size;
    int max_capacity;
    void **data;
    cmp_fn cmp;
};

PriorityQueue *pq_construct(cmp_fn cmp)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));

    pq->size = 0;
    pq->max_capacity = INITIAL_CAP;
    pq->cmp = cmp;
    pq->data = (void **)malloc(pq->max_capacity * sizeof(void *));

    return pq;
}

int pq_size(PriorityQueue *pq)
{
    return pq->size;
}

void _swap(PriorityQueue *pq, int i, int j)
{
    void *temp = pq->data[i];
    pq->data[i] = pq->data[j];
    pq->data[j] = temp;
}

void _heapify_up(PriorityQueue *pq, int i)
{
    if (i == 0)
        return;

    if (pq->cmp(pq->data[i], pq->data[(i - 1) / 2]) < 0)
    {
        _swap(pq, i, (i - 1) / 2);
        _heapify_up(pq, (i - 1) / 2);
    }
}

void pq_insert(PriorityQueue *pq, void *item)
{
    if (pq->size == pq->max_capacity)
    {
        pq->max_capacity *= 2;
        pq->data = (void **)realloc(pq->data, pq->max_capacity * sizeof(void *));
    }

    pq->data[pq->size] = item;

    _heapify_up(pq, pq->size);

    pq->size++;
}

void _heapify_down(PriorityQueue *pq, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int max = i;

    if (left < pq->size && pq->cmp(pq->data[left], pq->data[max]) < 0)
        max = left;

    if (right < pq->size && pq->cmp(pq->data[right], pq->data[max]) < 0)
        max = right;

    if (max == i)
        return;

    _swap(pq, i, max);
    _heapify_down(pq, max);
}

void *pq_remove(PriorityQueue *pq)
{
    if (pq->size == 0)
        return NULL;

    void *val = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];

    _heapify_down(pq, 0);

    return val;
}

void pq_destroy(PriorityQueue *pq)
{
    free(pq->data);
    free(pq);
}