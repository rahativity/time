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
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vi process(n), arrival(n), burst(n);
    vi completion(n), turnaround(n), waiting(n);
    vi is_completed(n);

    int i, j, temp, pos;
    int current_time = 0;
    int completed = 0;

    float totalTAT = 0;
    float totalWT = 0;
    float averageTAT, averageWT;

    for (i = 0; i < n; i++) {
        process[i] = i + 1;

        cout << "Enter arrival time of process " << process[i] << ": ";
        cin >> arrival[i];

        cout << "Enter burst time of process " << process[i] << ": ";
        cin >> burst[i];

        completion[i] = -1;
        is_completed[i] = 0;
    }

    for (i = 0; i < n; i++) {
        pos = i;

        for (j = i + 1; j < n; j++) {
            if (arrival[j] < arrival[pos]) {
                pos = j;
            }
        }

        temp = arrival[i];
        arrival[i] = arrival[pos];
        arrival[pos] = temp;

        temp = burst[i];
        burst[i] = burst[pos];
        burst[pos] = temp;

        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

    while (completed != n) {
        int min_burst = 9999;
        int index = -1;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= current_time && is_completed[i] == 0) {
                if (burst[i] < min_burst) {
                    min_burst = burst[i];
                    index = i;
                }
                else if (burst[i] == min_burst &&
                         arrival[i] < arrival[index]) {
                    index = i;
                }
            }
        }

        if (index != -1) {
            completion[index] = current_time + burst[index];
            turnaround[index] = completion[index] - arrival[index];
            waiting[index] = turnaround[index] - burst[index];

            totalTAT = totalTAT + turnaround[index];
            totalWT = totalWT + waiting[index];

            current_time = completion[index];

            is_completed[index] = 1;
            completed++;
        }
        else {
            current_time++;
        }
    }

    averageTAT = totalTAT / n;
    averageWT = totalWT / n;

    cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for (i = 0; i < n; i++) {
        cout << "P" << process[i] << "\t"
             << arrival[i] << "\t\t"
             << burst[i] << "\t\t"
             << completion[i] << "\t\t"
             << turnaround[i] << "\t\t"
             << waiting[i] << "\n";
    }

    cout << "\nTotal Turnaround Time = " << fixed << setprecision(0) << totalTAT;
    cout << "\nTotal Waiting Time    = " << fixed << setprecision(0) << totalWT;

    cout << "\nAverage Turnaround Time = " << fixed << setprecision(2) << averageTAT;
    cout << "\nAverage Waiting Time    = " << fixed << setprecision(2) << averageWT << "\n";

    return 0;
}
