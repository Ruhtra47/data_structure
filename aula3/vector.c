#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#define INITIAL_SIZE 10

Vector *vector_construct()
{
    Vector *v = (Vector *)malloc(sizeof(Vector));

    v->size = 0;
    v->allocated = INITIAL_SIZE;

    v->data = (data_type *)malloc(v->allocated * sizeof(data_type));

    return v;
}

void vector_push_back(Vector *v, data_type val)
{
    if (v->size >= v->allocated)
    {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated * sizeof(data_type));
    }

    v->data[v->size] = val;
    v->size++;
}

data_type vector_get(Vector *v, int i)
{
    return v->data[i];
}

void vector_set(Vector *v, int i, data_type val)
{
    if (i < 0 || i >= v->size)
    {
        printf("Indice invalido!");
        exit(1);
    }
    v->data[i] = val;
}

int vector_size(Vector *v)
{
    return v->size;
}

int vector_find(Vector *v, data_type val, compare_fn compare)
{
    for (int i = 0; i < v->size; i++)
    {
        if (!compare(val, v->data[i]))
        {
            return i;
        }
    }
    return -1;
}

data_type vector_max(Vector *v, compare_fn compare)
{
    data_type max = v->data[0];

    for (int i = 1; i < v->size; i++)
    {
        max = (compare(v->data[i], max) > 0) ? v->data[i] : max;
    }

    return max;
}

data_type vector_min(Vector *v, compare_fn compare)
{
    data_type min = v->data[0];

    for (int i = 1; i < v->size; i++)
    {
        min = (compare(v->data[i], min) < 0) ? v->data[i] : min;
    }

    return min;
}

int vector_argmax(Vector *v, compare_fn compare)
{
    return vector_find(v, vector_max(v, compare), compare);
}

int vector_argmin(Vector *v, compare_fn compare)
{
    return vector_find(v, vector_min(v, compare), compare);
}

data_type vector_remove(Vector *v, int i)
{
    data_type rem = v->data[i];

    for (int j = i; j < v->size - 1; j++)
    {
        v->data[j] = v->data[j + 1];
    }
    v->size--;

    return rem;
}

data_type vector_pop_front(Vector *v)
{
    return vector_remove(v, 0);
}

data_type vector_pop_back(Vector *v)
{
    return vector_remove(v, v->size - 1);
}

void vector_insert(Vector *v, int i, data_type val)
{
    if (v->size >= v->allocated - 1)
    {
        v->allocated *= 2;
        v->data = (data_type *)realloc(v->data, v->allocated);
    }

    v->size++;

    for (int j = v->size - 1; j >= i; j--)
    {
        v->data[j] = v->data[j - 1];
    }
    v->data[i] = val;
}

void vector_swap(Vector *v, int i, int j)
{
    data_type temp = v->data[i];

    v->data[i] = v->data[j];
    v->data[j] = temp;
}

void vector_sort(Vector *v, compare_fn compare)
{
    for (int j = 0; j < v->size; j++)
    {
        int sorted = 1;
        for (int i = 0; i < v->size - 1; i++)
        {
            if (compare(v->data[i], v->data[i + 1]) > 0)
            {
                vector_swap(v, i, i + 1);
                sorted = 0;
            }
        }
        if (sorted)
            break;
    }
}

int vector_binary_search(Vector *v, data_type val, compare_fn compare)
{
    int left = 0, right = v->size - 1, mid = v->size / 2;

    while (left <= right)
    {
        if (compare(v->data[mid], val) > 0)
        {
            right = mid - 1;
            mid = (right + left) / 2;
        }
        else if (compare(v->data[mid], val) < 0)
        {
            left = mid + 1;
            mid = (right + left) / 2;
        }
        else if (!compare(v->data[mid], val))
        {
            return mid;
        }
    }
    return -1;
}

void vector_reverse(Vector *v)
{
    for (int i = 0; i < v->size / 2; i++)
    {
        vector_swap(v, i, v->size - i - 1);
    }
}

Vector *vector_copy(Vector *v)
{
    Vector *nv = vector_construct();

    for (int i = 0; i < v->size; i++)
    {
        vector_push_back(nv, v->data[i]);
    }

    return nv;
}

void vector_clear(Vector *v)
{
    for (int i = 0; i < v->size; i++)
    {
        // free(v->data[i]);
        // v->data[i] = 0;
        vector_pop_back(v);
    }
}

void vector_destroy(Vector *v)
{
    free(v->data);
    free(v);
}
