#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "forward_list.h"

// typedef struct HashTable HashTable;
struct HashTable
{
    int table_size;
    int n_elements;
    HashFunction hash_fn;
    CmpFunction cmp_fn;

    ForwardList **buckets;
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
    HashTable *table;
    int bucket_index;
    Node *node_cur;
    int table_elem;
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));

    ht->table_size = table_size;
    ht->n_elements = 0;
    ht->hash_fn = hash_fn;
    ht->cmp_fn = cmp_fn;
    ht->buckets = (ForwardList **)calloc(table_size, sizeof(ForwardList *));

    return ht;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val)
{
    int hash = h->hash_fn(h, key);

    if (h->buckets[hash] == NULL)
        h->buckets[hash] = forward_list_construct();

    Node *n = h->buckets[hash]->head;
    while (n != NULL)
    {
        HashTableItem *cur_item = (HashTableItem *)n->value;
        if (!h->cmp_fn(key, cur_item->key))
        {
            void *old_val = cur_item->val;
            cur_item->val = val;
            return old_val;
        }
        n = n->next;
    }
    HashTableItem *new_item = (HashTableItem *)malloc(sizeof(HashTableItem));
    new_item->key = key;
    new_item->val = val;
    h->n_elements++;
    forward_list_push_front(h->buckets[hash], new_item);
    return NULL;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key)
{
    int hash = h->hash_fn(h, key);

    if (h->buckets[hash] == NULL)
        return NULL;

    Node *n = h->buckets[hash]->head;
    while (n != NULL)
    {
        HashTableItem *cur_item = (HashTableItem *)n->value;
        if (!h->cmp_fn(key, cur_item->key))
        {
            return cur_item->val;
        }
        n = n->next;
    }
    return NULL;
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key)
{
    int hash = h->hash_fn(h, key);

    Node *prev = h->buckets[hash]->head;
    Node *cur = h->buckets[hash]->head->next;

    if (!h->cmp_fn(((HashTableItem *)prev->value)->key, key))
    {
        void *value = ((HashTableItem *)prev->value)->val;
        h->buckets[hash]->head = cur;
        return value;
    }

    while (cur != NULL)
    {
        HashTableItem *item = (HashTableItem *)cur->value;

        if (!h->cmp_fn(item->key, key))
        {
            void *value = item->val;
            prev->next = cur->next;
            cur = cur->next;
            return value;
        }
        prev = prev->next;
        cur = cur->next;
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

    it->table = h;
    it->bucket_index = 0;
    it->node_cur = h->buckets[it->bucket_index]->head;
    it->table_elem = 0;

    return it;
}

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it)
{
    return (it->table->table_size == it->table_elem) ? 1 : 0;
}

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it)
{
}

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it)
{
    free(it);
}