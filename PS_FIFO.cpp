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

    vi process(n), arrival(n), execution(n), completion(n);
    vi turnaround(n), waiting(n);

    int i, j, pos, temp;
    float averageTAT = 0, averageWT = 0;

    for (i = 0; i < n; i++) {
        process[i] = i + 1;

        cout << "Enter arrival time of process " << process[i] << ": ";
        cin >> arrival[i];

        cout << "Enter execution time of process " << process[i] << ": ";
        cin >> execution[i];

        completion[i] = -1;
    }

    for (i = 0; i < n; i++) {
        pos = i;

        for (j = i + 1; j < n; j++) {
            if (arrival[pos] > arrival[j]) {
                pos = j;
            }
        }

        temp = arrival[i];
        arrival[i] = arrival[pos];
        arrival[pos] = temp;

        temp = execution[i];
        execution[i] = execution[pos];
        execution[pos] = temp;

        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

    for (i = 0; i < n; i++) {
        if (i == 0) {
            completion[i] = arrival[i] + execution[i];
        }
        else {
            if (completion[i - 1] > arrival[i]) {
                completion[i] = completion[i - 1] + execution[i];
            }
            else {
                completion[i] = arrival[i] + execution[i];
            }
        }
    }

    for (i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - execution[i];

        averageTAT = averageTAT + turnaround[i];
        averageWT = averageWT + waiting[i];
    }

    averageTAT = averageTAT / n;
    averageWT = averageWT / n;

    cout << "\nProcess\tArrival\tExecution\tCompletion\tTAT\tWT\n";

    for (i = 0; i < n; i++) {
        cout << "P" << process[i] << "\t"
             << arrival[i] << "\t"
             << execution[i] << "\t\t"
             << completion[i] << "\t\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\n";
    }

    cout << "\nAverage Turnaround Time = " << fixed << setprecision(2) << averageTAT;
    cout << "\nAverage Waiting Time    = " << fixed << setprecision(2) << averageWT << "\n";

    return 0;
}
