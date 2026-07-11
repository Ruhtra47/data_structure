#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    string name, category;
    int id, priority;

    Process(string name, string category, int id, int priority) : name(name), category(category), id(id), priority(priority) {}

    void print()
    {
        cout << this->name << " " << this->category << " " << this->id << " " << this->priority << "\n";
    }

    ~Process() {}
};

class CompareProcess
{
public:
    bool operator()(const Process &a, const Process &b)
    {
        return a.priority < b.priority;
    }
};

int main()
{
    int n;
    cin >> n;

    priority_queue<Process, vector<Process>, CompareProcess> pq;

    for (int i = 0; i < n; i++)
    {
        string name, category;
        int id, prio;

        cin >> name >> category >> id >> prio;

        pq.emplace(name, category, id, prio);
    }

    for (int i = 0; i < n; i++)
    {
        Process p = pq.top();
        pq.pop();

        p.print();
    }
}