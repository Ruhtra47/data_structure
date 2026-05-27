#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "list.h"

// typedef struct Queue
// {
//     List *list;
// } Queue;

Queue *queue_construct()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->list = list_construct();
    return q;
}

int queue_size(Queue *q)
{
    return list_size(q->list);
}

void queue_enqueue(Queue *q, data_type data)
{
    list_push_front(q->list, data);
}

data_type queue_dequeue(Queue *q)
{
    return list_pop_back(q->list);
}

void queue_destroy(Queue *q)
{
    list_destroy(q->list);
    free(q);
}