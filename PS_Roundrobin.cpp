#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()

int main() {
    int n, i, tq;

    cout << "Enter the number of processes: ";
    cin >> n;

    vi process(n), arrival(n), burst(n), remaining(n), completion(n);
    vi waiting(n), turnaround(n);

    for (i = 0; i < n; i++) {
        process[i] = i + 1;
        cout << "Enter arrival time of process " << process[i] << ": ";
        cin >> arrival[i];
        cout << "Enter burst time of process " << process[i] << ": ";
        cin >> burst[i];

        remaining[i] = burst[i];
        completion[i] = 0;
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;

    vi visited(n);
    for (i = 0; i < n; i++)
        visited[i] = 0;

    for (i = 0; i < n; i++) {
        if (arrival[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            int next_arrival = 9999;

            for (i = 0; i < n; i++) {
                if (remaining[i] > 0 && arrival[i] > time && arrival[i] < next_arrival) {
                    next_arrival = arrival[i];
                }
            }

            time = next_arrival;

            for (i = 0; i < n; i++) {
                if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }

        int idx = queue[front++];

        if (remaining[idx] > tq) {
            time += tq;
            remaining[idx] -= tq;
        } else {
            time += remaining[idx];
            remaining[idx] = 0;
            completion[idx] = time;
            completed++;
        }

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (remaining[idx] > 0) {
            queue[rear++] = idx;
        }
    }

    float total_wt = 0, total_tat = 0;

    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        total_wt += waiting[i];
        total_tat += turnaround[i];

        cout << process[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t\t"
             << turnaround[i] << "\t\t"
             << waiting[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << (total_wt / n);
    cout << "\nAverage Turnaround Time: " << fixed << setprecision(2) << (total_tat / n) << "\n";

    return 0;
}
