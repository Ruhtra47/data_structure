#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product.h"

// #define MAX_NAME_LENGTH 64

// typedef struct product Product;
struct product
{
    char name[MAX_NAME_LENGTH];
    float price;
    float discount;
    int qtd;
    int n_sales;
};

Product *product_constructor(const char *name, float price, int qtd)
{
    if (price < 0 || qtd < 0)
    {
        printf("VALOR INVALIDO\n");
        return NULL;
    }

    Product *p = (Product *)malloc(sizeof(Product));

    strcpy(p->name, name);
    p->price = price;
    p->discount = 0.0;
    p->qtd = qtd;
    p->n_sales = 0;

    return p;
}

const char *product_get_name(Product *product)
{
    return product->name;
}

float product_get_price(Product *product)
{
    return product->price;
}

float product_get_discount(Product *product)
{
    return product->discount;
}

int product_get_qtd(Product *product)
{
    return product->qtd;
}

int product_get_sales(Product *product)
{
    return product->n_sales;
}

void product_set_name(Product *product, const char *name)
{
    if (strlen(name) > 64)
    {
        printf("VALOR INVALIDO\n");
        return;
    }
    strncpy(product->name, name, 64);
}

void product_set_price(Product *product, float price)
{
    if (price <= 0)
    {
        printf("VALOR INVALIDO\n");
        return;
    }
    product->price = price;
}

void product_set_discount(Product *product, float discount)
{
    if (discount <= 0 || discount > 1)
    {
        printf("VALOR INVALIDO\n");
        return;
    }
    product->discount = discount;
}

void product_sell(Product *product, int quantity)
{
    if (quantity > product->qtd)
    {
        printf("ESTOQUE INSUFICIENTE\n");
        return;
    }

    if (quantity <= 0)
    {
        printf("QUANTIDADE INVALIDA\n");
    }

    product->n_sales += quantity;
    product->qtd -= quantity;
}

void product_buy(Product *product, int quantity)
{
    if (quantity <= 0)
    {
        printf("QUANTIDADE INVALIDA\n");
        return;
    }

    product->qtd += quantity;
}

float product_get_price_with_discount(Product *product)
{
    return ((float)product->price * (1 - product->discount));
}

void product_print(void *product)
{
    Product *p = (Product *)product;
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n", p->name, p->price, p->discount, product_get_price_with_discount(p), p->qtd, p->n_sales);
}

void product_destructor(void *product)
{
    free(product);
}

// --------------------------------------------------
// Exercicio 2

int product_compare_name(const void *a, const void *b)
{
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;

    return strcmp(p1->name, p2->name);
}

int product_compare_price(const void *a, const void *b)
{
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;

    return ((p1->price - p2->price < 0) ? -1 : (p1->price - p2->price > 0) ? 1
                                                                           : 0);
}

int product_compare_sales(const void *a, const void *b)
{
    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;

    return (p1->n_sales - p2->n_sales);
}