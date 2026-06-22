#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "list.h"

// typedef struct HashTable HashTable;

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

// typedef int (*HashFunction)(HashTable *, void *);
// typedef int (*CmpFunction)(void *k1, void *k2);

// typedef struct
// {
//     void *key;
//     void *val;
// } HashTableItem;

// typedef struct HashTableIterator HashTableIterator;
struct HashTableIterator
{
    HashTable *hash_table;
    int bucket_index;
    Node *cur_node;
    int cur_element;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));

    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;
    h->table_size = table_size;
    h->n_elements = 0;

    h->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));
    for (int i = 0; i < table_size; i++)
    {
        h->buckets[i] = forward_list_construct();
    }

    return h;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val)
{
    int hash_val = h->hash_fn(h, key);

    ForwardList *list = h->buckets[hash_val];
    Node *n = list->head;

    while (n != NULL)
    {
        HashTableItem *item = (HashTableItem *)n->value;

        if (!h->cmp_fn(key, item->key))
        {
            void *old_value = item->val;
            item->val = val;
            return old_value;
        }

        n = n->next;
    }

    HashTableItem *new_item = (HashTableItem *)malloc(sizeof(HashTableItem));
    new_item->key = key;
    new_item->val = val;

    h->n_elements++;

    forward_list_push_front(list, new_item);
    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key)
{
    int hash_val = h->hash_fn(h, key);

    ForwardList *list = h->buckets[hash_val];
    Node *n = list->head;

    while (n != NULL)
    {
        HashTableItem *item = (HashTableItem *)n->value;

        if (!h->cmp_fn(key, item->key))
        {
            return item->val;
        }

        n = n->next;
    }

    return NULL;
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key)
{
    int hash_val = h->hash_fn(h, key);

    ForwardList *list = h->buckets[hash_val];

    // compara head
    HashTableItem *item_head = (HashTableItem *)list->head->value;
    if (!h->cmp_fn(item_head->key, key))
    {
        void *old_value = item_head->val;
        Node *to_remove = list->head;
        list->head = list->head->next;
        node_destroy(to_remove);
        return old_value;
    }

    Node *cur = list->head->next;
    Node *prev = list->head;

    while (cur != NULL)
    {
        HashTableItem *item = (HashTableItem *)cur->value;

        if (!h->cmp_fn(item->key, key))
        {
            void *value_removed = item->val;

            prev->next = cur->next;
            node_destroy(cur);
            return value_removed;
        }

        cur = cur->next;
        prev = prev->next;
    }
    return NULL;
}

// numero de buckets
int hash_table_size(HashTable *h)
{
    return h->table_size;
}

// numero de elementos inseridos
int hash_table_num_elems(HashTable *h)
{
    return h->n_elements;
}

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h)
{
    for (int i = 0; i < h->table_size; i++)
    {
        if (h->buckets[i] != NULL)
        {
            Node *n = h->buckets[i]->head;

            while (n != NULL)
            {
                HashTableItem *item = (HashTableItem *)n->value;
                free(item->key);
                free(item->val);
                n = n->next;
            }

            forward_list_destroy(h->buckets[i]);
        }
    }

    free(h->buckets);
    free(h);
}

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h)
{
    HashTableIterator *it = (HashTableIterator *)malloc(sizeof(HashTableIterator));

    it->hash_table = h;
    it->bucket_index = 0;
    it->cur_node = h->buckets[it->bucket_index]->head;
    it->cur_element = 0;

    return it;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it)
{
    return (it->cur_element == it->hash_table->n_elements) ? 1 : 0;
}

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
    while (it->cur_node == NULL)
    {
        it->bucket_index++;
        it->cur_node = it->hash_table->buckets[it->bucket_index]->head;
    }

    HashTableItem *item = (HashTableItem *)it->cur_node->value;
    it->cur_node = it->cur_node->next;
    it->cur_element++;
    return item;
}

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it)
{
    free(it);
}

Vector *hash_to_vector(HashTable *h)
{
    Vector *v = vector_construct();

    HashTableIterator *it = hash_table_iterator(h);
    while (!hash_table_iterator_is_over(it))
    {
        HashTableItem *item = hash_table_iterator_next(it);
        vector_push_back(v, item);
    }

    hash_table_iterator_destroy(it);
    return v;
}