#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    queue<string> q;

    for (int i = 0; i < n; i++)
    {
        string cmd;
        cin >> cmd;

        if (!cmd.compare("ENQUEUE"))
        {
            string val;
            cin >> val;

            q.emplace(val);
        }
        else if (!cmd.compare("DEQUEUE"))
        {
            string popped = q.front();
            q.pop();

            cout << popped << "\n";
        }
    }

    return 0;
}