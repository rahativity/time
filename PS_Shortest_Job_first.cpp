#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival;
    int burst;
    int completion = 0;
    int tat = 0;
    int wt = 0;
    bool completed = false;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter arrival time of process " << p[i].id << ": ";
        cin >> p[i].arrival;
        cout << "Enter burst time of process " << p[i].id << ": ";
        cin >> p[i].burst;
    }

    // Sort initially by arrival time
    stable_sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed < n) {
        int best_idx = -1;

        // Find arrived process with the shortest burst time
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= current_time && !p[i].completed) {
                if (best_idx == -1 || p[i].burst < p[best_idx].burst) {
                    best_idx = i;
                } else if (p[i].burst == p[best_idx].burst && p[i].arrival < p[best_idx].arrival) {
                    best_idx = i;
                }
            }
        }

        if (best_idx != -1) {
            current_time += p[best_idx].burst;
            p[best_idx].completion = current_time;
            p[best_idx].tat = p[best_idx].completion - p[best_idx].arrival;
            p[best_idx].wt = p[best_idx].tat - p[best_idx].burst;

            totalTAT += p[best_idx].tat;
            totalWT += p[best_idx].wt;

            p[best_idx].completed = true;
            completed++;
        } else {
            // CPU is idle, advance time
            current_time++;
        }
    }

    float averageTAT = totalTAT / n;
    float averageWT = totalWT / n;

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].arrival << "\t\t"
             << p[i].burst << "\t\t"
             << p[i].completion << "\t\t"
             << p[i].tat << "\t\t"
             << p[i].wt << "\n";
    }

    cout << "\nTotal Turnaround Time = " << fixed << setprecision(0) << totalTAT;
    cout << "\nTotal Waiting Time    = " << fixed << setprecision(0) << totalWT;
    cout << "\nAverage Turnaround Time = " << fixed << setprecision(2) << averageTAT;
    cout << "\nAverage Waiting Time    = " << fixed << setprecision(2) << averageWT << "\n";

    return 0;
}
