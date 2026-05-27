#ifndef _QUEUE_H
#define _QUEUE_H

#include "list.h"

typedef struct Queue
{
    List *list;
} Queue;

Queue *queue_construct();
int queue_size(Queue *q);
void queue_enqueue(Queue *q, data_type data);
data_type queue_dequeue(Queue *q);
void queue_destroy(Queue *q);

#endif