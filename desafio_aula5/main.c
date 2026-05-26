#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"
#include "queue.h"
#include "priority_queue.h"

int cmp_so(const void *a, const void *b)
{
    Program *pa = (Program *)a;
    Program *pb = (Program *)b;

    int pa_prio = program_get_priority(pa);
    int pb_prio = program_get_priority(pb);

    if (pa_prio != pb_prio)
        return pb_prio - pa_prio;

    int pa_load = program_get_load(pa);
    int pb_load = program_get_load(pb);

    if (pa_load != pb_load)
        return pa_load - pb_load;

    return strcmp(program_get_name(pa), program_get_name(pb));
}

int cmp_user(const void *a, const void *b)
{
    Program *pa = (Program *)a;
    Program *pb = (Program *)b;

    int pa_prio = program_get_priority(pa);
    int pb_prio = program_get_priority(pb);

    if (pa_prio != pb_prio)
        return pb_prio - pa_prio;

    int pa_last = program_get_last_use(pa);
    int pb_last = program_get_last_use(pb);

    if (pa_last != pb_last)
        return pa_last - pb_last;

    return strcmp(program_get_name(pa), program_get_name(pb));
}

int main(void)
{
    int n;
    scanf("%d", &n);

    Program **programs = (Program **)malloc(n * sizeof(Program *));

    for (int i = 0; i < n; i++)
    {
        char name[64], type[5];
        int prio, load, it_start;
        scanf("%s %s %d %d %d", name, type, &prio, &load, &it_start);
        programs[i] = program_construct_with_type(name, type, prio, load, it_start);
    }

    Queue *rt_queue = queue_construct(n + 1);

    PriorityQueue *so_queue = pq_construct(cmp_so);
    PriorityQueue *user_queue = pq_construct(cmp_user);

    int turn = 0, iteration = 0, programs_added = 0;

    while (1)
    {
        for (int i = 0; i < n; i++)
        {
            if (programs[i] == NULL)
                continue;
            if (program_get_it_begin(programs[i]) == iteration)
            {
                char *type = program_get_type(programs[i]);
                if (strcmp(type, "RT") == 0)
                    queue_push_back(rt_queue, programs[i]);
                else if (strcmp(type, "SO") == 0)
                    pq_insert(so_queue, programs[i]);
                else
                    pq_insert(user_queue, programs[i]);

                programs[i] = NULL;
                programs_added++;
            }
        }

        int rt_empty = queue_is_empty(rt_queue);
        int so_empty = (pq_size(so_queue) == 0);
        int user_empty = (pq_size(user_queue) == 0);

        if (programs_added == n && rt_empty && so_empty && user_empty)
            break;

        if (rt_empty && so_empty && user_empty)
        {
            iteration++;
            continue;
        }

        Program *selected = NULL;
        if (!rt_empty)
        {
            selected = (Program *)queue_pop_front(rt_queue);
        }
        else
        {
            if (turn == 0)
            {
                if (!so_empty)
                {
                    selected = (Program *)pq_remove(so_queue);
                    turn = 1;
                }
                else
                {
                    selected = (Program *)pq_remove(user_queue);
                    turn = 1;
                    turn = 0;
                }
            }
            else
            {
                if (!user_empty)
                {
                    selected = (Program *)pq_remove(user_queue);
                    turn = 0;
                }
                else
                {
                    selected = (Program *)pq_remove(so_queue);
                    turn = 1;
                }
            }
        }

        program_decrease_load(selected);

        if (program_get_load(selected) == 0)
        {
            printf("%s %d\n", program_get_name(selected), iteration);
            program_destroy(selected);
        }
        else
        {
            program_set_last_use(selected, iteration);

            char *type = program_get_type(selected);
            if (strcmp(type, "RT") == 0)
                queue_push_back(rt_queue, selected);
            else if (strcmp(type, "SO") == 0)
                pq_insert(so_queue, selected);
            else
                pq_insert(user_queue, selected);
        }

        iteration++;
    }

    for (int i = 0; i < n; i++)
    {
        if (programs[i] != NULL)
            program_destroy(programs[i]);
    }

    free(programs);
    queue_destroy(rt_queue);
    pq_destroy(so_queue);
    pq_destroy(user_queue);

    return 0;
}
