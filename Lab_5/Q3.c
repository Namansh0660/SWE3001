/*
3.  Consider a junction of road where 4 roads meet at this junction, every often
    there is a problem of jamming of vehicles at this junction. To overcome this 
    problem a traffic signal was planned to be installed at the signal. The 
    operation of the signal is planned in such a way that, the vehicles in each lane
    of the road will be allowed only for 3 minutes and then stopped. The chance will
    be given to next lane of the road. write a c program implement a scheduling 
    algorithm to illustrate how the vehicles crossed the junction with the minimum
    waiting time. Calculate average waiting time and average turnaround time, 
    dislpay gant chart and all results on screen.(busttime = #vehicles) (Round Robin)
    */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int id;
    int lane;
} Vehicle;

void roundRobinScheduling(Vehicle vehicles[], int n, int time_quantum) {
    int remaining_time[MAX];
    int waiting_time[MAX];
    int turnaround_time[MAX];
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        remaining_time[i] = vehicles[i].lane * 3; // Each lane gets 3 minutes
        waiting_time[i] = 0;
    }
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; 
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

        if (done == 1) 
            break;
    }
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + (vehicles[i].lane * 3);
    }
    printf("Vehicle ID\tLane\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\t\t%d\n", vehicles[i].id, vehicles[i].lane, 
               waiting_time[i], turnaround_time[i]);
    }
    printf("\nGantt Chart:\n");
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

    printf("Enter the number of vehicles: ");
    scanf("%d", &n);
    printf("Enter the time quantum for each lane (in minutes): ");
    scanf("%d", &time_quantum);

    Vehicle *vehicles = (Vehicle*)malloc(n * sizeof(Vehicle));

    for (int i = 0; i < n; i++) {
        vehicles[i].id = i + 1;
        printf("\nEnter details for Vehicle %d:\n", i + 1);
        printf("Lane: ");
        scanf("%d", &vehicles[i].lane);
    }

    roundRobinScheduling(vehicles, n, time_quantum);

    // Free allocated memory
    free(vehicles);

    return 0;
}




#include <stdio.h>
#define TimeQuantum 3
#define VehicleCrossingRate 10

int main() {
    int road[4] = {0, 0, 0, 0};
    int time = 0, turn = 0, totalVehicles = 0, btime = 0;
    int wait[4] = {0}, tot[4] = {0};

    // Input the number of vehicles for each road
    for (int i = 0; i < 4; i++) {
        printf("Enter number of vehicles in road %d: ", i);
        scanf("%d", &road[i]);
        totalVehicles += road[i];
    }

    printf("\nGantt Chart:\n");

    // Simulate the traffic signal scheduling
    while (totalVehicles > 0) {
        printf("> Time %d\t Road %d\t Vehicles %d\n", time, turn, road[turn]);

        if (road[turn] > 0) {
            int crossing = (road[turn] >= VehicleCrossingRate) ? VehicleCrossingRate : road[turn];
            road[turn] -= crossing;
            totalVehicles -= crossing;

            if (road[turn] <= 0) {
                printf(">> Road %d is empty.\n", turn);
            }

            wait[turn] += time - tot[turn];
            tot[turn] = time + 1;
        }

        time++;

        if ((time % TimeQuantum == 0) || (road[turn] == 0)) {
            do {
                turn = (turn + 1) % 4;
            } while ((road[turn] <= 0) && (totalVehicles > 0));
        }
    }

    printf("\nAverage Waiting Time:\n");
    for (int i = 0; i < 4; i++) {
        printf("Road %d: %.2f minutes\n", i, (float) wait[i] / road[i]);
    }

    printf("\nAverage Turnaround Time: %.2f minutes\n", (float) (time - 1) / totalVehicles);

    return 0;
}
