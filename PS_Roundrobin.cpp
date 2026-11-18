#include <bits/stdc++.h>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion = 0;
    int tat = 0;
    int wt = 0;
};

int main() {
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter arrival time of process " << p[i].id << ": ";
        cin >> p[i].arrival;
        cout << "Enter burst time of process " << p[i].id << ": ";
        cin >> p[i].burst;
        p[i].remaining = p[i].burst;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    queue<int> q;
    vector<bool> in_queue(n, false);
    int time = 0, completed = 0;

    // Enqueue processes arriving at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrival == 0) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while (completed < n) {
        // If ready queue is empty, advance time to the next arrival
        if (q.empty()) {
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0 && p[i].arrival > time) {
                    if (next_arrival == -1 || p[i].arrival < next_arrival) {
                        next_arrival = p[i].arrival;
                    }
                }
            }

            if (next_arrival != -1) {
                time = next_arrival;
                for (int i = 0; i < n; i++) {
                    if (p[i].arrival <= time && p[i].remaining > 0 && !in_queue[i]) {
                        q.push(i);
                        in_queue[i] = true;
                    }
                }
            }
        }

        int idx = q.front();
        q.pop();

        int exec_time = min(p[idx].remaining, tq);
        time += exec_time;
        p[idx].remaining -= exec_time;

        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            completed++;
        }

        // Add newly arrived processes while idx was executing
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && !in_queue[i]) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        // If current process still has burst left, re-add to ready queue
        if (p[idx].remaining > 0) {
            q.push(idx);
        }
    }

    float total_wt = 0, total_tat = 0;
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].completion - p[i].arrival;
        p[i].wt = p[i].tat - p[i].burst;

        total_wt += p[i].wt;
        total_tat += p[i].tat;

        cout << p[i].id << "\t"
             << p[i].arrival << "\t"
             << p[i].burst << "\t"
             << p[i].completion << "\t\t"
             << p[i].tat << "\t\t"
             << p[i].wt << "\n";
    }

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (total_wt / n);
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << (total_tat / n) << "\n";

    return 0;
}
