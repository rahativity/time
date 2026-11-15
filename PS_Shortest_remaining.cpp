#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

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

    int time = 0, completed = 0;

    while (completed < n) {
        int min_index = -1;

        // Find process with shortest remaining time among arrived processes
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (min_index == -1 || p[i].remaining < p[min_index].remaining) {
                    min_index = i;
                }
            }
        }

        // If no process has arrived yet, jump to the next arrival time
        if (min_index == -1) {
            int next_arrival = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].arrival > time) {
                    if (next_arrival == -1 || p[i].arrival < next_arrival) {
                        next_arrival = p[i].arrival;
                    }
                }
            }
            time = next_arrival;
            continue;
        }

        // Execute process for up to time quantum
        int exec_time = min(p[min_index].remaining, tq);
        p[min_index].remaining -= exec_time;
        time += exec_time;

        if (p[min_index].remaining == 0) {
            p[min_index].completion = time;
            completed++;
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
