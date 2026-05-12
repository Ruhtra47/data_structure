#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

// typedef struct Queue Queue;
struct Queue
{
    int max_capacity;
    int size;
    int start;
    int end;
    void **data;
};

// Create an queue
Queue *queue_constructor(int max_capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));

    q->max_capacity = max_capacity;
    q->size = 0;
    q->start = 0;
    q->end = 0;
    q->data = (void **)malloc(max_capacity * sizeof(void *));

    return q;
}

// Add an element
void queue_add(Queue *queue, void *data)
{
    queue->data[queue->end] = data;
    queue->end = (queue->end + 1) % queue->max_capacity;
    queue->size++;
}

// Remove the oldest element in the queue
void *queue_remove(Queue *queue)
{
    void *removed = queue->data[queue->start];
    queue->start = (queue->start + 1) % queue->max_capacity;
    queue->size--;

    return removed;
}

// Return the number of elements in the queue
int queue_size(Queue *queue)
{
    return queue->size;
}

// Return 1 if the queue is full and 0, otherwise
int queue_is_full(Queue *queue)
{
    return queue->size >= queue->max_capacity ? 1 : 0;
}

// Return 1 if the queue is empty and 0, otherwise
int queue_is_empty(Queue *queue)
{
    return queue->size == 0 ? 1 : 0;
}

// Free the data structure.
// IMPORTANT: the user of the lib is responsible for removing and freeing elements
// remaining in the queue. In the queue is not empty when the functions is called,
// the function will not release them.
void queue_destroy(Queue *queue)
{
    free(queue->data);
    free(queue);
}