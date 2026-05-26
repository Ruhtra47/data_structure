#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

// typedef struct Queue Queue;
struct Queue
{
    int size;
    int max_capacity;
    int start;
    int end;
    void **data;
};

Queue *queue_construct(int max_capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->size = 0;
    q->max_capacity = max_capacity;
    q->start = 0;
    q->end = 0;
    q->data = (void **)malloc(max_capacity * sizeof(void *));

    return q;
}

void queue_push_back(Queue *q, void *item)
{
    q->data[q->end] = item;
    q->end = (q->end + 1) % q->max_capacity;

    q->size++;
}

void *queue_pop_front(Queue *q)
{
    void *val = q->data[q->start];
    q->start = (q->start + 1) % q->max_capacity;
    q->size--;

    return val;
}

int queue_is_empty(Queue *q)
{
    return q->size == 0 ? 1 : 0;
}

void queue_destroy(Queue *q)
{
    free(q->data);
    free(q);
}