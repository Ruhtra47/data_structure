#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

typedef struct PriorityQueue PriorityQueue;

typedef int (*cmp_fn)(const void *, const void *);

PriorityQueue *pq_construct(cmp_fn cmp);
int pq_size(PriorityQueue *pq);
void pq_insert(PriorityQueue *pq, void *item);
void *pq_remove(PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq);

#endif