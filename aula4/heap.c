#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "vector.h"

struct Heap
{
    Vector *data;
    cmp_fn cmp;
};

// implementações das funções

// Cria um heap vazio
Heap *heap_construct(cmp_fn cmp)
{
    Heap *h = (Heap *)malloc(sizeof(Heap));

    h->data = vector_construct();
    h->cmp = cmp;

    return h;
}

// Libera memória do heap
void heap_destroy(Heap *h, void (*free_item)(void *))
{
    for (int i = 0; i < vector_size(h->data); i++)
    {
        free_item(vector_get(h->data, i));
    }
    vector_destroy(h->data);
    free(h);
}

// Insere um elemento no heap
void heap_push(Heap *h, data_type value)
{
    vector_push_back(h->data, value);

    // heapify_up
    // pai = (i-1)/2
    int i = vector_size(h->data) - 1;
    while (i >= 0)
    {
        if (h->cmp(vector_get(h->data, i), vector_get(h->data, (i - 1) / 2)) > 0)
        {
            vector_swap(h->data, i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
        else
        {
            break;
        }
    }
}

// Remove e retorna o elemento de maior prioridade
data_type heap_pop(Heap *h)
{
    vector_swap(h->data, vector_size(h->data) - 1, 0);
    data_type val = vector_pop_back(h->data);

    // heapify_down
    // left = 2*i + 1;
    // right = 2*i + 2;
    int i = 0;
    while (1)
    {
        if (2 * i + 2 < heap_size(h))
        {
            if (h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 2)) > 0 && h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 1)) > 0)
            {
                break;
            }
            else if (h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 1)) < 0 && h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 2)) < 0)
            {
                if (h->cmp(vector_get(h->data, 2 * i + 2), vector_get(h->data, 2 * i + 1)) > 0)
                {
                    vector_swap(h->data, i, 2 * i + 2);
                    i = 2 * i + 2;
                }
                else
                {
                    vector_swap(h->data, i, 2 * i + 1);
                    i = 2 * i + 1;
                }
            }
            else if (h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 2)) < 0)
            {
                vector_swap(h->data, i, 2 * i + 2);
                i = 2 * i + 2;
            }
            else if (h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 1)) < 0)
            {
                vector_swap(h->data, i, 2 * i + 1);
                i = 2 * i + 1;
            }
            else
            {
                break;
            }
        }
        else if (2 * i + 1 < heap_size(h))
        {
            if (h->cmp(vector_get(h->data, i), vector_get(h->data, 2 * i + 1)) < 0)
            {
                vector_swap(h->data, i, 2 * i + 1);
                i = 2 * i + 1;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return val;
}

void heap_print_array(Heap *h, void (*print_elem)(void *elem))
{
    for (int i = 0; i < heap_size(h); i++)
    {
        print_elem(vector_get(h->data, i));
    }
}

// Retorna o número de elementos
int heap_size(Heap *h)
{
    return vector_size(h->data);
}

// Verifica se está vazio
int heap_empty(Heap *h)
{
    return vector_size(h->data) == 0 ? 1 : 0;
}
