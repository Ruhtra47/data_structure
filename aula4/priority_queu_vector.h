#ifndef _PRIORITY_QUEUE_VECTOR_H_
#define _PRIORITY_QUEUE_VECTOR_H_

typedef struct PriorityQueue PriorityQueue;

PriorityQueue *pq_constructor(compare_fn cmp_fn);
void pq_push(PriorityQueue *pq, void *data);
void *pq_pop(PriorityQueue *pq);
int pq_size(PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq, void (*free_item)(void *));

#endif