#include <stdio.h>

struct Process {
    int id;
    int parentId;
};

void printProcessTree(struct Process processes[], int size, int currentId, int level) {
    if (currentId == -1) {
        return;
    }

    for (int i = 0; i < level - 1; i++) {
        printf("│   ");
    }
    printf("Process ID: %d, Parent ID: %d\n", currentId, processes[currentId].parentId);

    for (int i = 0; i < size; i++) {
        if (processes[i].parentId == currentId) {
            printProcessTree(processes, size, processes[i].id, level + 1);
        }
    }
}

int main() {
    struct Process processes[] = {
        {0, -1},
        {1, 0},
        {2, 0},
        {3, 1},
        {4, 0},
        {5, 2},
        {6, 1},
        {7, 3},
        {8, 5}
    };
    
    int numProcesses = sizeof(processes) / sizeof(processes[0]);

    printf("Process Tree:\n");
    printProcessTree(processes, numProcesses, 0, 1);

    return 0;
}
