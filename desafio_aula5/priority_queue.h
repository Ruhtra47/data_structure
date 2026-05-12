#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *pq_construct();
int pq_size(PriorityQueue *pq);
void pq_insert(PriorityQueue *pq, void *item);
void *pq_remove(PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq);

#endif