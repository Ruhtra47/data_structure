#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "forward_list.h"

void print_data(data_type data)
{
    printf("%s\n", (char *)data);
}

int main()
{
    int num_instructions;
    scanf("%d", &num_instructions);

    ForwardList *list = forward_list_construct();

    for (int i = 0; i < num_instructions; i++)
    {
        char command[20];

        scanf("\n%s", command);

        if (strcmp(command, "PUSH_FRONT") == 0)
        {
            // O que aconteceria aqui se trocássemos a alocação dinâmica por alocação estática? Faça o teste!
            char *value = (char *)calloc(20, sizeof(char));
            scanf("%s\n", value);

            forward_list_push_front(list, value);
        }
        else if (strcmp(command, "POP") == 0)
        {
            int idx;
            scanf("%d", &idx);

            void *val = forward_list_pop_index(list, idx);
            if (val == NULL)
            {
                printf("INVALID INDEX\n");
                continue;
            }

            // PARA FAZER: libere o elemento retornado pelo pop
            free(val);
        }
    }

    forward_list_print(list, print_data);

    // PARA FAZER: a lista ainda pode ter elementos aqui. Libere-os.
    while (forward_list_size(list) > 0)
    {
        void *val = forward_list_pop_front(list);
        free(val);
    }

    forward_list_destroy(list);

    return 0;
}