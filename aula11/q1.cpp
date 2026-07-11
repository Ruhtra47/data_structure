#include <bits/stdc++.h>
using namespace std;

class Product
{
public:
    string name;
    float price, discount;
    unsigned int qtd, sales;

    Product(string name, float price, float discount, unsigned int qtd, unsigned int sales)
        : name(name), price(price), discount(discount), qtd(qtd), sales(sales) {}

    ~Product() {}

    void printProduct()
    {
        cout << "Product(" << this->name;
        printf(", %.2f, %.2f, %.2f, %d, %d)\n", this->price, this->discount, this->price, this->qtd, this->sales);
    }
};

bool compareName(const Product &a, const Product &b)
{
    return a.name < b.name;
}

bool comparePrice(const Product &a, const Product &b)
{
    return a.price < b.price;
}

bool compareSales(const Product &a, const Product &b)
{
    return a.sales < b.sales;
}

int main()
{
    int n;
    scanf("%d\n", &n);

    vector<Product> products;

    for (int i = 0; i < n; i++)
    {
        string name;
        float price;
        unsigned int qtd, sales;

        getline(cin, name);
        cin >> price >> qtd >> sales;
        cin.ignore();

        products.emplace_back(name, price, 0.0f, qtd - sales, sales);
    }

    char cmd;
    cin >> cmd;

    if (cmd == 'N')
        sort(products.begin(), products.end(), compareName);
    else if (cmd == 'P')
        sort(products.begin(), products.end(), comparePrice);
    else if (cmd == 'S')
        sort(products.begin(), products.end(), compareSales);

    for (auto p : products)
    {
        p.printProduct();
    }

    return 0;
}