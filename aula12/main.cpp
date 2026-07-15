#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Process {
public:
    string name, type;
    int priority, load, last_use, it_start;

    Process(string name, string type, int priority, int load, int last_use, int it_start) 
        : name(name), type(type), priority(priority), load(load), last_use(last_use), it_start(it_start) {}
};

struct CompareSO {
    bool operator()(const Process* a, const Process* b) const {
        if (a->priority != b->priority)
            return a->priority < b->priority;
        if (a->load != b->load)
            return a->load > b->load;
        return a->name > b->name;
    }
};

struct CompareUser {
    bool operator()(const Process* a, const Process* b) const {
        if (a->priority != b->priority)
            return a->priority < b->priority;
        if (a->last_use != b->last_use)
            return a->last_use > b->last_use;
        return a->name > b->name;
    }
};

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<Process*> processes;
    for (int i = 0; i < n; i++) {
        string name, type;
        int prio, load, it_start;
        cin >> name >> type >> prio >> load >> it_start;
        processes.push_back(new Process(name, type, prio, load, -1, it_start));
    }

    queue<Process*> rt_queue;
    priority_queue<Process*, vector<Process*>, CompareSO> so_queue;
    priority_queue<Process*, vector<Process*>, CompareUser> user_queue;

    int turn = 0, iteration = 0, programs_added = 0;

    while (true) {
        for (int i = 0; i < n; i++) {
            if (processes[i] == nullptr)
                continue;
            if (processes[i]->it_start == iteration) {
                if (processes[i]->type == "RT")
                    rt_queue.push(processes[i]);
                else if (processes[i]->type == "SO")
                    so_queue.push(processes[i]);
                else
                    user_queue.push(processes[i]);

                processes[i] = nullptr;
                programs_added++;
            }
        }

        bool rt_empty = rt_queue.empty();
        bool so_empty = so_queue.empty();
        bool user_empty = user_queue.empty();

        if (programs_added == n && rt_empty && so_empty && user_empty)
            break;

        if (rt_empty && so_empty && user_empty) {
            iteration++;
            continue;
        }

        Process* selected = nullptr;
        if (!rt_empty) {
            selected = rt_queue.front();
            rt_queue.pop();
        } else {
            if (turn == 0) {
                if (!so_empty) {
                    selected = so_queue.top();
                    so_queue.pop();
                    turn = 1;
                } else {
                    selected = user_queue.top();
                    user_queue.pop();
                    turn = 0;
                }
            } else {
                if (!user_empty) {
                    selected = user_queue.top();
                    user_queue.pop();
                    turn = 0;
                } else {
                    selected = so_queue.top();
                    so_queue.pop();
                    turn = 1;
                }
            }
        }

        selected->load--;

        if (selected->load == 0) {
            cout << selected->name << " " << iteration << "\n";
            delete selected;
        } else {
            selected->last_use = iteration;
            if (selected->type == "RT")
                rt_queue.push(selected);
            else if (selected->type == "SO")
                so_queue.push(selected);
            else
                user_queue.push(selected);
        }

        iteration++;
    }

    for (int i = 0; i < n; i++) {
        if (processes[i] != nullptr)
            delete processes[i];
    }

    return 0;
}