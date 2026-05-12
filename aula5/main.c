#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"

int main()
{
    int n;
    scanf("%d", &n);

    Deque *d = deque_construct();

    for (int i = 0; i < n; i++)
    {
        int val;
        char cmd[10];
        scanf("%s", cmd);

        if (!strcmp(cmd, "PUSH_BACK"))
        {
            scanf("%d", &val);

            deque_push_back(d, val);
        }
        else if (!strcmp(cmd, "PUSH_FRONT"))
        {
            scanf("%d", &val);

            deque_push_front(d, val);
        }
        else if (!strcmp(cmd, "POP_BACK"))
        {
            val = deque_pop_back(d);
            printf("%d\n", val);
        }
        else if (!strcmp(cmd, "POP_FRONT"))
        {
            val = deque_pop_front(d);
            printf("%d\n", val);
        }
        else if (!strcmp(cmd, "GET"))
        {
            int index;
            scanf("%d", &index);

            val = deque_get(d, index);
            printf("%d\n", val);
        }
    }

    deque_destroy(d);
}