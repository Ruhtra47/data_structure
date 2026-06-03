#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "forward_list.h"

// typedef struct HashTable HashTable;

// typedef int (*HashFunction)(HashTable *, void *);
// typedef int (*CmpFunction)(void *k1, void *k2);

// typedef struct
// {
//     void *key;
//     void *val;
// } HashTableItem;

// typedef struct HashTableIterator HashTableIterator;

struct HashTable
{
    ForwardList **buckets;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    int table_size;
    int n_elements;
};

struct HashTableIterator
{
};

// constroi a hash
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));

    h->table_size = table_size;
    h->n_elements = 0;
    h->buckets = (ForwardList **)malloc(table_size * sizeof(ForwardList *));
    h->hash_fn = hash_fn;
    h->cmp_fn = cmp_fn;

    return h;
}

void *_hash_item_value(HashTableItem *hi)
{
    return hi->val;
}

void *_hash_item_key(HashTableItem *hi)
{
    return hi->key;
}

// funcao para insercao/atualizacao de pares chave-valor em O(1).
// Se a chave ja existir, atualiza o valor e retorna o valor antigo para permitir desalocacao.
void *hash_table_set(HashTable *h, void *key, void *val)
{
    int key_val = h->hash_fn(h, key) % h->table_size;

    if (h->buckets[key_val] == NULL)
    {
        h->buckets[key_val] = forward_list_construct();
    }

    Node *n = h->buckets[key_val]->head;
    void *prev = NULL;
    int exist = 0;
    while (n != NULL)
    {
        if (!h->cmp_fn(val, _hash_item_value(n->value)))
        {
            // prev = node_construct(n->value, n->next);
            prev = n->value;
            HashTableItem *item = (HashTableItem *)malloc(sizeof(HashTableItem));
            n->value = item;
            exist = 1;
            break;
        }
        n = n->next;
    }

    if (!exist)
    {
        HashTableItem *item = (HashTableItem *)malloc(sizeof(HashTableItem));
        item->key = key;
        item->val = val;
        forward_list_push_front(h->buckets[key_val], item);
    }

    return prev;
}

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1).
void *hash_table_get(HashTable *h, void *key)
{
    int key_val = h->hash_fn(h, key) % h->table_size;

    if (h->buckets[key_val] == NULL)
        return NULL;

    Node *n = h->buckets[key_val]->head;
    while (n != NULL)
    {
        if (!h->cmp_fn(key, _hash_item_key(n->value)))
        {
        }
    }
}

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key);

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
void hash_table_destroy(HashTable *h);

// cria um novo iterador para a tabela hash
HashTableIterator *hash_table_iterator(HashTable *h);

// retorna 1 se o iterador chegou ao fim da tabela hash ou 0 caso contrario
int hash_table_iterator_is_over(HashTableIterator *it);

// retorna o proximo par chave valor da tabela hash
HashTableItem *hash_table_iterator_next(HashTableIterator *it);

// desaloca o iterador da tabela hash
void hash_table_iterator_destroy(HashTableIterator *it);