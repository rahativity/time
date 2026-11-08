#include <stdio.h>

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process[n], arrival[n], burst[n];
    int completion[n], turnaround[n], waiting[n];
    int is_completed[n];

    int i, j, temp, pos;
    int current_time = 0;
    int completed = 0;

    float totalTAT = 0;
    float totalWT = 0;
    float averageTAT, averageWT;

    // Input process details
    for (i = 0; i < n; i++) {
        process[i] = i + 1;

        printf("Enter arrival time of process %d: ", process[i]);
        scanf("%d", &arrival[i]);

        printf("Enter burst time of process %d: ", process[i]);
        scanf("%d", &burst[i]);

        completion[i] = -1;
        is_completed[i] = 0;
    }

    // Sorting processes based on arrival time
    for (i = 0; i < n; i++) {
        pos = i;

        for (j = i + 1; j < n; j++) {
            if (arrival[j] < arrival[pos]) {
                pos = j;
            }
        }

        // Swap arrival time
        temp = arrival[i];
        arrival[i] = arrival[pos];
        arrival[pos] = temp;

        // Swap burst time
        temp = burst[i];
        burst[i] = burst[pos];
        burst[pos] = temp;

        // Swap process ID
        temp = process[i];
        process[i] = process[pos];
        process[pos] = temp;
    }

    // Apply Shortest Job First (Non-Preemptive)
    while (completed != n) {

        int min_burst = 9999;
        int index = -1;

        // Find the shortest available process
        for (i = 0; i < n; i++) {

            if (arrival[i] <= current_time && is_completed[i] == 0) {

                if (burst[i] < min_burst) {
                    min_burst = burst[i];
                    index = i;
                }

                // If burst times are equal, select the one
                // that arrived first
                else if (burst[i] == min_burst &&
                         arrival[i] < arrival[index]) {
                    index = i;
                }
            }
        }

        // If a process is available
        if (index != -1) {

            completion[index] = current_time + burst[index];
            turnaround[index] = completion[index] - arrival[index];
            waiting[index] = turnaround[index] - burst[index];

            // Add to totals
            totalTAT = totalTAT + turnaround[index];
            totalWT = totalWT + waiting[index];

            // Update current time
            current_time = completion[index];

            is_completed[index] = 1;
            completed++;
        }

        // If no process has arrived yet
        else {
            current_time++;
        }
    }

    // Calculate averages
    averageTAT = totalTAT / n;
    averageWT = totalWT / n;

    // Printing the final process table
    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               process[i],
               arrival[i],
               burst[i],
               completion[i],
               turnaround[i],
               waiting[i]);
    }

    // Print total and average values
    printf("\nTotal Turnaround Time = %.0f", totalTAT);
    printf("\nTotal Waiting Time    = %.0f", totalWT);

    printf("\nAverage Turnaround Time = %.2f", averageTAT);
    printf("\nAverage Waiting Time    = %.2f\n", averageWT);

    return 0;
}

