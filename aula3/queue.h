#ifndef _QUEUE_H
#define _QUEUE_H

#include "vector.h"

typedef struct Queue Queue;

Queue *queue_construct();
void queue_destroy(void *q);
int queue_get_size(Queue *q);
void queue_enqueue(Queue *q, void *e);
void *queue_dequeue(Queue *q);

#endif