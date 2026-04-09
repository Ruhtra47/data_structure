#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

// typedef struct Queue Queue;
struct Queue
{
    Vector *v;
};

Queue *queue_construct()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->v = vector_construct();

    return q;
}

void queue_destroy(void *q)
{
    Queue *v = (Queue *)q;
    vector_destroy(v->v);
    free(q);
}

int queue_get_size(Queue *q)
{
    return vector_size(q->v);
}

void queue_enqueue(Queue *q, void *e)
{
    vector_push_back(q->v, e);
}

void *queue_dequeue(Queue *q)
{
    return vector_pop_back(q->v);
}