#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    stack<string> s;

    for (int i = 0; i < n; i++)
    {
        string cmd;
        cin >> cmd;

        if (!cmd.compare("PUSH"))
        {
            string value;
            cin >> value;

            s.push(value);
        }
        else if (!cmd.compare("POP"))
        {
            string value = s.top();
            s.pop();

            cout << value << "\n";
        }
    }

    return 0;
}