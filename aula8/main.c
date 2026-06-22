
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "vector.h"

int hash_str(int seed, int update_val, int table_size, void *data)
{
    char *str = (char *)data;
    int hash_val = 0, base = seed;
    int random_val = update_val;
    int size = strlen(str);

    for (int i = 0; i < size; i++)
    {
        hash_val = (hash_val * random_val + str[i]) % table_size;
        random_val = (random_val * base) % (table_size - 1);
    }

    return hash_val;
}

int main()
{
    int seed, update_val, table_size, n;
    scanf("%d %d %d %d", &seed, &update_val, &table_size, &n);

    char str[50];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", str);
        printf("%d\n", hash_str(seed, update_val, table_size, str));
    }

    return 0;
}
