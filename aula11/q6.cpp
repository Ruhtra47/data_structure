#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    deque<string> forno;
    deque<string> motoboy;

    for (int i = 0; i < n; i++)
    {
        string cmd;
        cin >> cmd;

        if (!cmd.compare("PEDIDO"))
        {
            string pizza;
            cin >> pizza;

            forno.emplace_back(pizza);
        }
        else if (!cmd.compare("FORNO_LIVRE"))
        {
            string pizza = forno.front();
            forno.pop_front();

            motoboy.emplace_back(pizza);
        }
        else if (!cmd.compare("MOTOBOY"))
        {
            string pizza = motoboy.front();
            motoboy.pop_front();

            cout << "ENTREGUE " << pizza << "\n";
        }
        else if (!cmd.compare("INSPECAO_FORNO"))
        {
            int index;
            cin >> index;

            string pizza = forno.at(index);
            cout << pizza << "\n";
        }
        else if (!cmd.compare("INSPECAO_ENTREGA"))
        {
            int index;
            cin >> index;

            string pizza = motoboy.at(index);
            cout << pizza << "\n";
        }
    }

    return 0;
}