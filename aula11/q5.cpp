#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    map<string, int> bt;

    for (int i = 0; i < n; i++)
    {
        string word;
        cin >> word;

        bt[word]++;
    }

    for (auto p : bt)
        cout << p.first << " " << p.second << "\n";

    return 0;
}