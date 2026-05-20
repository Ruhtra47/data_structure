#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "forward_list.h"
#include "node.h"

// typedef struct
// {
//     Node *head;
//     int size;
// } ForwardList;

/**
 * @brief Construct a new Linked List:: Linked List object
 *  Allocates memory for a new linked list and returns a pointer to it.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the linked list using forward_list_destroy().
 *
 */
ForwardList *forward_list_construct()
{
    ForwardList *fl = (ForwardList *)malloc(sizeof(ForwardList));

    fl->head = NULL;
    fl->size = 0;

    return fl;
}

/**
 * @brief Returns the size of the linked list.
 *  Returns the number of nodes in the linked list.
 * @param l
 * Pointer to the linked list.
 * @return int
 * Number of nodes in the linked list.
 *
 */
int forward_list_size(ForwardList *l)
{
    return l->size;
}

/**
 * @brief Pushes a new node to the front of the linked list.
 *  Allocates memory for a new node and inserts it at the front of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param data
 * Pointer to the data to be stored in the new node.
 *
 */
void forward_list_push_front(ForwardList *l, data_type data)
{
    Node *new_node = node_construct(data, l->head);
    l->head = new_node;
    l->size++;
}

/**
 * @brief Print the elements of the linked list.
 *  Print the elements of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param print_fn
 * Pointer to the function to print data_type values.
 *
 */
void forward_list_print(ForwardList *l, void (*print_fn)(data_type))
{
    Node *n = l->head;
    printf("[");
    while (n != NULL)
    {
        print_fn(node_value(n));
        n = node_next(n);
        if (n != NULL)
            printf(", ");
    }
    printf("]\n");
}

/**
 * @brief Returns the data stored in the node at the given index.
 * @param l
 * Pointer to the linked list.
 * @param i
 * Index of the node.
 * @return data_type
 * Data stored in the node at the given index.
 *
 */
data_type forward_list_get(ForwardList *l, int i)
{
    if (i >= l->size || i < 0)
    {
        printf("Indice inserido invalido\n");
        exit(1);
    }

    Node *n = l->head;

    for (int j = 0; j < i; j++)
    {
        n = node_next(n);
    }

    return node_value(n);
}

/**
 * @brief Remove the first node of the linked list and returns its data.
 * @param l
 * Pointer to the linked list.
 * @return data_type
 * Pointer to the data stored in the first node of the linked list that was removed.
 *
 */
data_type forward_list_pop_front(ForwardList *l)
{
    data_type removed = node_value(l->head);
    Node *to_free = l->head;
    l->head = node_next(l->head);
    node_destroy(to_free);
    l->size--;
    return removed;
}

/**
 * @brief Create a new list given by the reverse of the given list.
 * @param l
 * Pointer to the linked list.
 * @return ForwardList*
 * Pointer to the newly allocated linked list.
 */
ForwardList *forward_list_reverse(ForwardList *l)
{
    ForwardList *reversed = (ForwardList *)malloc(sizeof(ForwardList));

    Node *n = l->head;
    while (n != NULL)
    {
        forward_list_push_front(reversed, node_value(n));
        n = node_next(n);
    }

    return reversed;
}

/**
 * @brief Removes all nodes from the linked list.
 * Removes all nodes from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The caller is responsible for freeing the memory allocated for the data stored in the nodes.
 */
void forward_list_clear(ForwardList *l)
{
    // Node *n = l->head;
    // Node *to_remove = l->head;
    // while (n != NULL)
    // {
    //     n = node_next(n);
    //     node_destroy(to_remove);
    //     to_remove = n;
    // }

    forward_list_pop_front(l);
    while (l->head != NULL)
        forward_list_pop_front(l);
}

/**
 * @brief Removes all nodes with the given value from the linked list.
 * Removes all nodes with the given value from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @param val
 * Value to be removed from the linked list.
 */
void forward_list_remove(ForwardList *l, data_type val)
{
    if (node_value(l->head) == val)
    {
        forward_list_pop_front(l);
    }

    Node *cur = node_next(l->head);
    Node *ant = l->head;

    while (cur != NULL)
    {
        if (node_value(cur) == val)
        {
            Node *to_remove = cur;
            ant->next = cur->next;
            // ant = cur;
            cur = cur->next;
            node_destroy(to_remove);
            l->size--;
        }
        else
        {
            ant = cur;
            cur = cur->next;
        }
    }
}

/**
 * @brief Removes all duplicate values from the linked list.
 * Removes all duplicate values from the linked list and frees the memory allocated for them.
 * @param l
 * Pointer to the linked list.
 * @note
 * The linked list must be sorted.
 */
void forward_list_unique(ForwardList *l);

/**
 * @brief Adds all nodes from the given list to the end of the linked list.
 * @param l
 * Pointer to the linked list.
 * @param m
 * Pointer to the linked list to be added to the end of the linked list.
 */
void forward_list_cat(ForwardList *l, ForwardList *m)
{
    Node *n = m->head;
    for (int i = 0; i < m->size; i++)
    {
        forward_list_push_front(l, node_value(n));
        n = n->next;
    }
}

/**
 * @brief Sorts the linked list.
 * Sorts the linked list.
 * @param l
 * Pointer to the linked list.
 */
void forward_list_sort(ForwardList *l);

/**
 * @brief Destroys the linked list.
 *  Frees the memory allocated for the linked list and all its nodes.
 * @param l
 * Pointer to the linked list.
 *
 */
void forward_list_destroy(ForwardList *l)
{
    forward_list_clear(l);
    free(l);
}