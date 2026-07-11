#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, size;
    cin >> n >> size;

    unordered_map<string, string> h;

    for (int i = 0; i < n; i++)
    {
        string cmd;
        cin >> cmd;

        if (!cmd.compare("SET"))
        {
            string name, msg;
            cin >> name;
            cin.ignore();
            getline(cin, msg);

            h[name] = msg;
        }
        else if (!cmd.compare("GET"))
        {
            string name;
            cin >> name;

            cout << h[name] << "\n";
        }
    }

    return 0;
}