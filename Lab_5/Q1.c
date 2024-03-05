#include<stdio.h>

void fcfs(int arrival_time[], int n, int booking_time[]) {
    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    // Calculate waiting time for each person
    waiting_time[0] = 0;
    for(int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i-1] + booking_time[i-1] - arrival_time[i];
        total_waiting_time += waiting_time[i];
    }

    // Calculate turnaround time for each person
    for(int i = 0; i < n; i++) {
        turnaround_time[i] = booking_time[i] + waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    printf("-----------\n");
    printf("| ");
    for(int i = 0; i < n; i++) {
        printf(" P%d |", i+1);
    }
    printf("\n-----------\n");
    printf("0\t");
    for(int i = 0; i < n; i++) {
        printf("\t%d", turnaround_time[i]);
    }
    printf("\n\n");

    // Display waiting time and turnaround time for each person
    printf("Waiting Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d: %d\n", i+1, waiting_time[i]);
    }

    printf("\nTurnaround Time:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d: %d\n", i+1, turnaround_time[i]);
    }

    // Calculate and display average turnaround time
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter the number of people in the queue: ");
    scanf("%d", &n);

    int arrival_time[n], booking_time[n];
    printf("Enter arrival and booking times for each person:\n");
    for(int i = 0; i < n; i++) {
        printf("Arrival time for P%d: ", i+1);
        scanf("%d", &arrival_time[i]);
        printf("Booking time for P%d: ", i+1);
        scanf("%d", &booking_time[i]);
    }

    fcfs(arrival_time, n, booking_time);

    return 0;
}
