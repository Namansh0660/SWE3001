#include <stdio.h>
#include <stdlib.h>

// Structure to represent a customer
typedef struct {
    int id;
    int arrival_time;
    int distance;
    int priority; // Priority for case ii
} Customer;

// Function to compute waiting time for SJF
void findWaitingTimeSJF(Customer customers[], int n, int waiting_time[]) {
    int service_time[n];
    service_time[0] = 0;
    waiting_time[0] = 0;

    // Compute service time
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + customers[i - 1].distance;
        waiting_time[i] = service_time[i] - customers[i].arrival_time;

        if (waiting_time[i] < 0)
            waiting_time[i] = 0;
    }
}

// Function to compute waiting time for Priority scheduling
void findWaitingTimePriority(Customer customers[], int n, int waiting_time[]) {
    int service_time[n];
    service_time[0] = 0;
    waiting_time[0] = 0;

    // Compute service time
    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i - 1] + customers[i - 1].distance;
        waiting_time[i] = service_time[i] - customers[i].arrival_time;

        if (waiting_time[i] < 0)
            waiting_time[i] = 0;
    }
}

// Function to calculate turnaround time
void findTurnAroundTime(Customer customers[], int n, int waiting_time[], int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = customers[i].distance + waiting_time[i];
    }
}

// Function to compute average time
void findAvgTime(Customer customers[], int n) {
    int waiting_time[n], turnaround_time[n];

    // Find waiting time of all customers
    findWaitingTimeSJF(customers, n, waiting_time);

    // Find turnaround time for all customers
    findTurnAroundTime(customers, n, waiting_time, turnaround_time);

    // Display results
    printf("Customer ID\t Arrival Time\t Distance\t Waiting Time\t Turnaround Time\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", customers[i].id, customers[i].arrival_time, 
               customers[i].distance, waiting_time[i], turnaround_time[i]);
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("| Customer %d ", customers[i].id);
    }
    printf("|\n");

    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / (float)n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / (float)n);
}

int main() {
    int n;

    // Input number of customers
    printf("Enter the number of customers: ");
    scanf("%d", &n);

    // Allocate memory for customers
    Customer *customers = (Customer*)malloc(n * sizeof(Customer));

    // Input data for each customer
    for (int i = 0; i < n; i++) {
        customers[i].id = i + 1;
        printf("\nEnter details for Customer %d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &customers[i].arrival_time);
        printf("Distance: ");
        scanf("%d", &customers[i].distance);
        // For case ii
        printf("Priority/Frequency: ");
        scanf("%d", &customers[i].priority);
    }

    // Display results for SJF
    printf("\nResults for SJF (Shortest Job First):\n");
    findAvgTime(customers, n);

    // Display results for Priority scheduling
    printf("\nResults for Priority Scheduling:\n");
    findAvgTime(customers, n);

    // Free allocated memory
    free(customers);

    return 0;
}
