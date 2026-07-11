#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    forward_list<string> list;

    for (int i = 0; i < n; i++)
    {
        string cmd;
        cin >> cmd;

        if (!cmd.compare("ADD_BEGIN"))
        {
            string song;
            cin >> song;

            list.push_front(song);
        }
        else if (!cmd.compare("ADD_AFTER"))
        {
            string ref, song;
            cin >> ref >> song;

            for (auto it = list.begin(); it != list.end(); ++it)
            {
                if (*it == ref)
                {
                    list.insert_after(it, song);
                    break;
                }
            }
        }
        else if (!cmd.compare("REMOVE"))
        {
            string song;
            cin >> song;

            list.remove(song);
        }
    }

    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << "\n";
    }

    return 0;
}