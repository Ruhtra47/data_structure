#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct Queue Queue;

Queue *queue_construct(int max_capacity);
void queue_push_back(Queue *q, void *item);
void *queue_pop_front(Queue *q);
int queue_is_empty(Queue *q);
void queue_destroy(Queue *q);

#endif