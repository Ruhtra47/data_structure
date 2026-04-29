#ifndef _HEAP_H_
#define _HEAP_H_

// Função de comparação. Deve retornar valor > 0 se primeiro elemento tem maior prioridade e valor < 0 se o segundo em mais prioridade.
typedef int (*cmp_fn)(void *a, void *b);
typedef void *data_type;

typedef struct Heap Heap;

// Cria um heap vazio
Heap *heap_construct(cmp_fn cmp);

// Libera memória do heap
void heap_destroy(Heap *h, void (*free_item)(void *));

// Insere um elemento no heap
void heap_push(Heap *h, data_type value);

// Remove e retorna o elemento de maior prioridade
data_type heap_pop(Heap *h);

// Retorna o número de elementos
int heap_size(Heap *h);

void heap_print_array(Heap *h, void (*print_elem)(void *elem));

// Verifica se está vazio
int heap_empty(Heap *h);

#endif