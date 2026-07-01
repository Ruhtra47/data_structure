#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "vector.h"

// typedef struct
// {
//     void *key;
//     void *value;
// } KeyValPair;

typedef struct Node Node;

struct Node
{
    KeyValPair *pair;
    Node *left;
    Node *right;
};

// KeyValPair *key_val_pair_construct(void *key, void *val);
// void key_val_pair_destroy(KeyValPair *kvp);

// typedef int (*CmpFn)(void *, void *);
// typedef void (*KeyDestroyFn)(void *);
// typedef void (*ValDestroyFn)(void *);

// typedef struct BinaryTree BinaryTree;

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
    int size;
};

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{

    BinaryTree *bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    bt->size = 0;

    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
    Node *n = bt->root;
    Node *last = NULL;
    int dir = 0;

    while (n != NULL)
    {
        if (bt->cmp_fn(key, n->pair->key) > 0)
        {
            last = n;
            n = n->right;
            dir = 1;
        }
        else
        {
            last = n;
            n = n->left;
            dir = -1;
        }
    }

    n = (Node *)malloc(sizeof(Node));
    n->left = NULL;
    n->right = NULL;

    KeyValPair *item = (KeyValPair *)malloc(sizeof(KeyValPair));
    item->key = key;
    item->value = value;
    n->pair = item;

    if (last != NULL)
    {
        if (dir > 0)
            last->right = n;
        else
            last->left = n;
    }
    else
    {
        bt->root = n;
    }

    bt->size++;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value);

int binary_tree_empty(BinaryTree *bt)
{
    return (bt->size == 0);
}

void binary_tree_remove(BinaryTree *bt, void *key);

KeyValPair *binary_tree_min(BinaryTree *bt);
KeyValPair *binary_tree_max(BinaryTree *bt);
KeyValPair *binary_tree_pop_min(BinaryTree *bt);
KeyValPair *binary_tree_pop_max(BinaryTree *bt);
Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);

void *recursive_get(BinaryTree *bt, Node *n, void *key)
{
    if (n == NULL)
    {
        return NULL;
    }

    if (!bt->cmp_fn(key, n->pair->value))
    {
        return n->pair->value;
    }
    else if (bt->cmp_fn(key, n->pair->value) > 0)
    {
        return recursive_get(bt, n->right, key);
    }
    else
    {
        return recursive_get(bt, n->left, key);
    }
}

void *binary_tree_get(BinaryTree *bt, void *key)
{
    Node *n = bt->root;
    return recursive_get(bt, n, key);
}

void recursive_destroy(BinaryTree *bt, Node *n)
{
    if (!n)
        return;

    recursive_destroy(bt, n->left);
    recursive_destroy(bt, n->right);

    bt->key_destroy_fn(n->pair->key);
    bt->val_destroy_fn(n->pair->value);
    free(n->pair);
    free(n);
    bt->size--;
}

void binary_tree_destroy(BinaryTree *bt)
{
    Node *n = bt->root;
    recursive_destroy(bt, n);
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt);

Vector *binary_tree_inorder_traversal(BinaryTree *bt);
Vector *binary_tree_preorder_traversal(BinaryTree *bt);
Vector *binary_tree_postorder_traversal(BinaryTree *bt);
Vector *binary_tree_levelorder_traversal(BinaryTree *bt);

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt);
Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt);