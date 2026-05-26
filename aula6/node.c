#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

// typedef int data_type;

// typedef struct Node
// {
//     data_type value;
//     struct Node *next;
// } Node;

Node *node_construct(data_type value, Node *next)
{
    Node *n = (Node *)malloc(sizeof(Node));

    n->value = value;
    n->next = next;

    return n;
}

// data_type node_value(Node *node) {
//     return node->value;
// }

// Node *node_next(Node *node) {
//     return node->next;
// }

void node_destroy(Node *n)
{
    free(n);
}