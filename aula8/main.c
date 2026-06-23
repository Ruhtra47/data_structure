#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"
#include "vector.h"
#include "node.h"

int hash_fn(HashTable *h, void *data)
{
    char *str = (char *)data;
    int hash = 0;
    int base = 127;
    int size = strlen(str);

    for (int i = 0; i < size; i++)
    {
        hash = (base * hash + str[i]) % hash_table_size(h);
    }

    return hash;
}

int cmp_str(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int cmp_vector(void *a, void *b)
{
    HashTableItem *item_a = (HashTableItem *)a;
    HashTableItem *item_b = (HashTableItem *)b;

    return cmp_str(item_a->key, item_b->key);
}

int main()
{
    int n;
    scanf("%d", &n);

    HashTable *h = hash_table_construct(n, hash_fn, cmp_str);

    for (int i = 0; i < n; i++)
    {
        char *str = (char *)malloc(30 * sizeof(char));
        scanf(" %s", str);

        void *prev_val = hash_table_get(h, str);
        if (prev_val == NULL)
        {
            int *new_val = (int *)malloc(sizeof(int));
            *new_val = 1;
            hash_table_set(h, str, new_val);
        }
        else
        {
            (*(int *)prev_val)++;
            hash_table_set(h, str, prev_val);
        }
    }

    Vector *v = hash_to_vector(h);
    vector_sort(v, cmp_vector);
    for (int i = 0; i < vector_size(v); i++)
    {
        HashTableItem *item = (HashTableItem *)vector_get(v, i);
        printf("%s %d\n", (char *)item->key, *(int *)item->val);
    }

    vector_destroy(v);
    hash_table_destroy(h);
}