#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrival;
    int execution;
    int completion;
    int tat;
    int wt;
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
        cout << "Enter execution time of process " << p[i].id << ": ";
        cin >> p[i].execution;
    }

    // Sort processes by arrival time (FCFS order)
    stable_sort(p.begin(), p.end(), [](const Process &a, const Process &b) {
        return a.arrival < b.arrival;
    });

    int current_time = 0;
    float totalTAT = 0, totalWT = 0;

    for (int i = 0; i < n; i++) {
        // If CPU is idle, advance time to the arrival of this process
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        current_time += p[i].execution;
        p[i].completion = current_time;
        p[i].tat = p[i].completion - p[i].arrival;
        p[i].wt = p[i].tat - p[i].execution;

        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    cout << "\nProcess\tArrival\tExecution\tCompletion\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].arrival << "\t"
             << p[i].execution << "\t\t"
             << p[i].completion << "\t\t"
             << p[i].tat << "\t"
             << p[i].wt << "\n";
    }

    cout << "\nAverage Turnaround Time = " << fixed << setprecision(2) << (totalTAT / n);
    cout << "\nAverage Waiting Time    = " << fixed << setprecision(2) << (totalWT / n) << "\n";

    return 0;
}
