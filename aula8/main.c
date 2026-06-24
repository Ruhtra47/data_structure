#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_fn(void *data, int table_size)
{
    char *str = (char *)data;
    int hash_val = 0, base = 27183;
    int random_val = 31415;
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
    int seed, update, table_size, n;
    scanf("%d %d %d %d", &seed, &update, &table_size, &n);

    char str[30];
    for (int i = 0; i < n; i++)
    {
        scanf(" %s", str);

        printf("%d\n", hash_fn(str, table_size));
    }
}