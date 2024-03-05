#include <stdio.h>
#include <stdlib.h>

#define MAX_VEHICLES 100

// Structure to represent a vehicle
typedef struct {
    int id;
    int lane;
} Vehicle;

// Function to simulate Round Robin scheduling for traffic signal
void roundRobinScheduling(Vehicle vehicles[], int n, int time_quantum) {
    int remaining_time[MAX_VEHICLES];
    int waiting_time[MAX_VEHICLES];
    int turnaround_time[MAX_VEHICLES];
    int current_time = 0;

    // Initialize remaining time for each vehicle
    for (int i = 0; i < n; i++) {
        remaining_time[i] = vehicles[i].lane * 3; // Each lane gets 3 minutes
        waiting_time[i] = 0;
    }

    // Simulate Round Robin scheduling
    while (1) {
        int done = 1;

        // Traverse each vehicle
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // At least one vehicle is remaining
                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    waiting_time[i] = current_time - (vehicles[i].lane * 3);
                    remaining_time[i] = 0;
                }
            }
        }

        if (done == 1) // All vehicles have completed
            break;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + (vehicles[i].lane * 3);
    }

    // Display results
    printf("Vehicle ID\tLane\tWaiting Time\tTurnaround Time\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t\t%d\n", vehicles[i].id, vehicles[i].lane, 
               waiting_time[i], turnaround_time[i]);
    }

    // Display Gantt chart
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("| Vehicle %d ", vehicles[i].id);
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
    int n, time_quantum;

    // Input number of vehicles and time quantum
    printf("Enter the number of vehicles: ");
    scanf("%d", &n);
    printf("Enter the time quantum for each lane (in minutes): ");
    scanf("%d", &time_quantum);

    // Allocate memory for vehicles
    Vehicle *vehicles = (Vehicle*)malloc(n * sizeof(Vehicle));

    // Input data for each vehicle
    for (int i = 0; i < n; i++) {
        vehicles[i].id = i + 1;
        printf("\nEnter details for Vehicle %d:\n", i + 1);
        printf("Lane: ");
        scanf("%d", &vehicles[i].lane);
    }

    // Perform Round Robin scheduling
    roundRobinScheduling(vehicles, n, time_quantum);

    // Free allocated memory
    free(vehicles);

    return 0;
}
