#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int size;
};

struct Partition {
    int id;
    int size;
    int allocated;
};

void bestFit(struct Process processes[], int numProcesses, struct Partition partitions[], int numPartitions) {
    for (int i = 0; i < numProcesses; i++) {
        int bestFitIndex = -1;
        for (int j = 0; j < numPartitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                if (bestFitIndex == -1 || partitions[j].size < partitions[bestFitIndex].size) {
                    bestFitIndex = j;
                }
            }
        }
        if (bestFitIndex != -1) {
            partitions[bestFitIndex].allocated = 1;
            printf("Process %d of size %dKB allocated to Partition %d of size %dKB\n",
                processes[i].pid, processes[i].size, partitions[bestFitIndex].id, partitions[bestFitIndex].size);
        } else {
            printf("Process %d of size %dKB cannot be allocated\n", processes[i].pid, processes[i].size);
        }
    }
}

void worstFit(struct Process processes[], int numProcesses, struct Partition partitions[], int numPartitions) {
    for (int i = 0; i < numProcesses; i++) {
        int worstFitIndex = -1;
        for (int j = 0; j < numPartitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                if (worstFitIndex == -1 || partitions[j].size > partitions[worstFitIndex].size) {
                    worstFitIndex = j;
                }
            }
        }
        if (worstFitIndex != -1) {
            partitions[worstFitIndex].allocated = 1;
            printf("Process %d of size %dKB allocated to Partition %d of size %dKB\n",
                processes[i].pid, processes[i].size, partitions[worstFitIndex].id, partitions[worstFitIndex].size);
        } else {
            printf("Process %d of size %dKB cannot be allocated\n", processes[i].pid, processes[i].size);
        }
    }
}

void firstFit(struct Process processes[], int numProcesses, struct Partition partitions[], int numPartitions) {
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numPartitions; j++) {
            if (partitions[j].allocated == 0 && partitions[j].size >= processes[i].size) {
                partitions[j].allocated = 1;
                printf("Process %d of size %dKB allocated to Partition %d of size %dKB\n",
                    processes[i].pid, processes[i].size, partitions[j].id, partitions[j].size);
                break; // Allocation successful, move to next process
            }
        }
    }
}

int main() {
    struct Partition partitions[] = {
        {1, 20, 0},
        {2, 100, 0},
        {3, 40, 0},
        {4, 200, 0},
        {5, 10, 0}
    };
    struct Process processes[] = {
        {1, 90},
        {2, 50},
        {3, 30},
        {4, 40}
    };
    int numPartitions = sizeof(partitions) / sizeof(partitions[0]);
    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    int choice;
    printf("Choose the memory allocation algorithm:\n");
    printf("1. Best Fit\n2. Worst Fit\n3. First Fit\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Memory Allocation using Best Fit Algorithm:\n");
            bestFit(processes, numProcesses, partitions, numPartitions);
            break;
        case 2:
            printf("Memory Allocation using Worst Fit Algorithm:\n");
            worstFit(processes, numProcesses, partitions, numPartitions);
            break;
        case 3:
            printf("Memory Allocation using First Fit Algorithm:\n");
            firstFit(processes, numProcesses, partitions, numPartitions);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    return 0;
}
