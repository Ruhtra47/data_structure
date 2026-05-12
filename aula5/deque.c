#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

#define MAX_CAPACITY 50

// typedef struct Deque Deque;
struct Deque
{
    int max_capacity;
    int size;
    int start;
    int end;
    int *data;
};

Deque *deque_construct()
{
    Deque *d = (Deque *)malloc(sizeof(Deque));

    d->max_capacity = MAX_CAPACITY;
    d->size = 0;
    d->start = 0;
    d->end = 0;
    d->data = (int *)malloc(d->max_capacity * sizeof(int));

    return d;
}

void deque_push_back(Deque *f, int item)
{
    f->data[f->end] = item;
    f->end = (f->end + 1) % f->max_capacity;
    f->size++;
}

void deque_push_front(Deque *f, int item)
{
    f->start = (f->start - 1 + f->max_capacity) % f->max_capacity;
    f->data[f->start] = item;
    f->size++;
}

int deque_pop_back(Deque *f)
{
    f->end = (f->end - 1 + f->max_capacity) % f->max_capacity;
    int val = f->data[f->end];
    f->size--;

    return val;
}
int deque_pop_front(Deque *f)
{
    int val = f->data[f->start];
    f->start = (f->start + 1) % f->max_capacity;
    f->size--;

    return val;
}

int deque_get(Deque *f, int idx)
{
    return f->data[(f->start + idx) % f->max_capacity];
}

void deque_destroy(Deque *f)
{
    free(f->data);
    free(f);
}