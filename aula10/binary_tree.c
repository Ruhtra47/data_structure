#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_tree.h"
#include "vector.h"

typedef struct Node Node;

struct Node
{
    KeyValPair *pair;
    Node *left;
    Node *right;
};

struct BinaryTree
{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

Node *node_construct(void *key, void *value)
{
    Node *n = (Node *)malloc(sizeof(Node));

    n->pair = key_val_pair_construct(key, value);
    n->left = NULL;
    n->right = NULL;

    return n;
}

void node_destroy(BinaryTree *bt, Node *n)
{
    bt->key_destroy_fn(n->pair->key);
    bt->val_destroy_fn(n->pair->value);
    key_val_pair_destroy(n->pair);
    free(n);
}

// typedef struct
// {
//     void *key;
//     void *value;
// } KeyValPair;

KeyValPair *key_val_pair_construct(void *key, void *val)
{
    KeyValPair *kvp = (KeyValPair *)malloc(sizeof(KeyValPair));

    kvp->key = key;
    kvp->value = val;

    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp)
{
    free(kvp);
}

// typedef int (*CmpFn)(void *, void *);
// typedef void (*KeyDestroyFn)(void *);
// typedef void (*ValDestroyFn)(void *);

// typedef struct BinaryTree BinaryTree;

BinaryTree *binary_tree_construct(
    CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,
    ValDestroyFn val_destroy_fn)
{
    BinaryTree *bt = (BinaryTree *)malloc(sizeof(BinaryTree));

    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;

    return bt;
}

void binary_tree_add(BinaryTree *bt, void *key, void *value)
{
    Node *new_node = node_construct(key, value);

    if (bt->root == NULL)
    {
        bt->root = new_node;
        return;
    }

    Node *current = bt->root;

    while (1)
    {
        int cmp = bt->cmp_fn(key, current->pair->key);

        if (cmp < 0)
        {
            if (current->left == NULL)
            {
                current->left = new_node;
                break;
            }

            current = current->left;
        }
        else if (cmp > 0)
        {
            if (current->right == NULL)
            {
                current->right = new_node;
                break;
            }

            current = current->right;
        }
        else
        {
            bt->key_destroy_fn(current->pair->key);
            bt->val_destroy_fn(current->pair->value);

            current->pair->key = key;
            current->pair->value = value;

            key_val_pair_destroy(new_node->pair);
            free(new_node);
            return;
        }
    }
}

Node *add_recursive(BinaryTree *bt, Node *node, void *key, void *value)
{
    if (node == NULL)
    {
        return node_construct(key, value);
    }

    int cmp = bt->cmp_fn(key, node->pair->key);

    if (cmp < 0)
    {
        node->left = add_recursive(bt, node->left, key, value);
    }
    else if (cmp > 0)
    {
        node->right = add_recursive(bt, node->right, key, value);
    }
    else
    {
        bt->key_destroy_fn(node->pair->key);
        bt->val_destroy_fn(node->pair->value);
        node->pair->key = key;
        node->pair->value = value;
    }

    return node;
}

void binary_tree_add_recursive(BinaryTree *bt, void *key, void *value)
{
    bt->root = add_recursive(bt, bt->root, key, value);
}

int binary_tree_empty(BinaryTree *bt)
{
    return (bt->root == NULL);
}

Node *remove_min_node(Node *root, Node **minNode)
{
    if (root->left == NULL)
    {
        *minNode = root;
        return root->right;
    }

    root->left = remove_min_node(root->left, minNode);
    return root;
}

Node *remove_node(BinaryTree *bt, Node *root, void *key)
{
    if (root == NULL)
        return NULL;

    int cmp = bt->cmp_fn(key, root->pair->key);

    if (cmp < 0)
    {
        root->left = remove_node(bt, root->left, key);
    }
    else if (cmp > 0)
    {
        root->right = remove_node(bt, root->right, key);
    }
    else
    {
        if (root->left == NULL && root->right == NULL) // Nó folha
        {
            node_destroy(bt, root);
            return NULL;
        }

        if (root->left == NULL) // 1 filho
        {
            Node *tmp = root->right;
            node_destroy(bt, root);
            return tmp;
        }
        if (root->right == NULL)
        {
            Node *tmp = root->left;
            node_destroy(bt, root);
            return tmp;
        }

        // 2 filhos
        Node *successor = NULL;
        root->right = remove_min_node(root->right, &successor);

        KeyValPair *tmp = root->pair;
        root->pair = successor->pair;
        successor->pair = tmp;

        node_destroy(bt, successor);
    }

    return root;
}

void binary_tree_remove(BinaryTree *bt, void *key)
{
    bt->root = remove_node(bt, bt->root, key);
}

Node *subtree_min(Node *node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

Node *subtree_max(Node *node)
{
    while (node->right != NULL)
        node = node->right;
    return node;
}

KeyValPair *binary_tree_min(BinaryTree *bt)
{
    Node *n = subtree_min(bt->root);
    return n->pair;
}

KeyValPair *binary_tree_max(BinaryTree *bt)
{
    Node *n = subtree_max(bt->root);
    return n->pair;
}

KeyValPair *binary_tree_pop_min(BinaryTree *bt)
{
    Node *parent = NULL;
    Node *curr = bt->root;

    while (curr->left != NULL)
    {
        parent = curr;
        curr = curr->left;
    }

    if (parent == NULL)
        bt->root = curr->right;
    else
        parent->left = curr->right;

    KeyValPair *pair = curr->pair;
    free(curr);

    return pair;
}

KeyValPair *binary_tree_pop_max(BinaryTree *bt)
{
    Node *parent = NULL;
    Node *curr = bt->root;

    while (curr->right != NULL)
    {
        parent = curr;
        curr = curr->right;
    }

    if (parent == NULL)
        bt->root = curr->left;
    else
        parent->right = curr->left;

    KeyValPair *pair = curr->pair;
    free(curr);

    return pair;
}

Vector *binary_tree_interval(BinaryTree *bt, void *min_key, void *max_key);

void *binary_tree_get(BinaryTree *bt, void *key)
{
    Node *current = bt->root;

    while (current != NULL)
    {
        int cmp = bt->cmp_fn(key, current->pair->key);

        if (cmp == 0)
            return current->pair->value;

        if (cmp < 0)
            current = current->left;
        else
            current = current->right;
    }

    return NULL;
}

void destroy_nodes(BinaryTree *bt, Node *node)
{
    if (node == NULL)
        return;

    destroy_nodes(bt, node->left);
    destroy_nodes(bt, node->right);

    node_destroy(bt, node);
}

void binary_tree_destroy(BinaryTree *bt)
{
    destroy_nodes(bt, bt->root);
    free(bt);
}

void print_node(Node *node)
{
    if (node == NULL)
    {
        printf("NULL");
        return;
    }

    printf("(%d, ", *(int *)node->pair->key);
    print_node(node->left);
    printf(", ");
    print_node(node->right);
    printf(")");
}

// a funcao abaixo pode ser util para debug, mas nao eh obrigatoria.
void binary_tree_print(BinaryTree *bt)
{
    print_node(bt->root);
    printf("\n");
}

Vector *binary_tree_inorder_traversal(BinaryTree *bt)
{
    Vector *result = vector_construct();
    Vector *stack = vector_construct();

    Node *current = bt->root;

    while (current != NULL || vector_size(stack) > 0)
    {
        while (current != NULL)
        {
            vector_push_back(stack, current);
            current = current->left;
        }

        current = (Node *)vector_pop_back(stack);
        vector_push_back(result, current->pair);
        current = current->right;
    }
    vector_destroy(stack);
    return result;
}

Vector *binary_tree_preorder_traversal(BinaryTree *bt)
{
    Vector *result = vector_construct();

    if (bt->root == NULL)
        return result;

    Vector *stack = vector_construct();

    vector_push_back(stack, bt->root);

    while (vector_size(stack) > 0)
    {
        Node *current = (Node *)vector_pop_back(stack);

        vector_push_back(result, current->pair);

        if (current->right != NULL)
            vector_push_back(stack, current->right);

        if (current->left != NULL)
            vector_push_back(stack, current->left);
    }

    vector_destroy(stack);

    return result;
}

Vector *binary_tree_postorder_traversal(BinaryTree *bt)
{
    Vector *result = vector_construct();

    if (bt->root == NULL)
        return result;

    Vector *s1 = vector_construct();
    Vector *s2 = vector_construct();

    vector_push_back(s1, bt->root);

    while (vector_size(s1) > 0)
    {
        Node *current = (Node *)vector_pop_back(s1);

        vector_push_back(s2, current);

        if (current->left != NULL)
            vector_push_back(s1, current->left);
        if (current->right != NULL)
            vector_push_back(s1, current->right);
    }

    while (vector_size(s2) > 0)
    {
        Node *current = (Node *)vector_pop_back(s2);
        vector_push_back(result, current->pair);
    }

    vector_destroy(s1);
    vector_destroy(s2);

    return result;
}

Vector *binary_tree_levelorder_traversal(BinaryTree *bt)
{
    Vector *result = vector_construct();

    if (bt->root == NULL)
        return result;

    Vector *queue = vector_construct();

    vector_push_back(queue, bt->root);

    while (vector_size(queue) > 0)
    {
        Node *current = (Node *)vector_pop_front(queue);

        vector_push_back(result, current->pair);

        if (current->left != NULL)
            vector_push_back(queue, current->left);
        if (current->right != NULL)
            vector_push_back(queue, current->right);
    }

    vector_destroy(queue);

    return result;
}

void inorder_recursive(Node *node, Vector *v)
{
    if (node == NULL)
        return;

    inorder_recursive(node->left, v);
    vector_push_back(v, node->pair);
    inorder_recursive(node->right, v);
}

void preorder_recursive(Node *node, Vector *v)
{
    if (node == NULL)
        return;

    vector_push_back(v, node->pair);
    preorder_recursive(node->left, v);
    preorder_recursive(node->right, v);
}

void postorder_recursive(Node *node, Vector *v)
{
    if (node == NULL)
        return;

    postorder_recursive(node->left, v);
    postorder_recursive(node->right, v);
    vector_push_back(v, node->pair);
}

Vector *binary_tree_inorder_traversal_recursive(BinaryTree *bt)
{
    Vector *v = vector_construct();
    inorder_recursive(bt->root, v);
    return v;
}

Vector *binary_tree_preorder_traversal_recursive(BinaryTree *bt)
{
    Vector *v = vector_construct();
    preorder_recursive(bt->root, v);
    return v;
}

Vector *binary_tree_postorder_traversal_recursive(BinaryTree *bt)
{
    Vector *v = vector_construct();
    postorder_recursive(bt->root, v);
    return v;
}