#include<stdio.h>

struct process {
    int pid;
    int ppid;
};

void displayProcessTree(struct process processes[], int n, int pid, int level) {
    if (pid == -1) {
        return;
    }
    for (int i = 0; i < level - 1; i++) {
        printf(" ");
    }
    if (level > 1) {
        printf("------");
    }
    printf("Process ID: %d, Parent ID: %d\n", pid, processes[pid].ppid);
    for (int i = 0; i < n; i++) {
        if (processes[i].ppid == pid) {
            displayProcessTree(processes, n, processes[i].pid, level + 1);
        }
    }
}

int main() {
    struct process processes[] = {
        {0, -1},
        {1, 0},
        {2, 0},
        {3, 1},
        {4, 0},
        {5, 2},
        {6, 1},
        {7, 3},
        {4, 5}
    };
    int n = sizeof(processes) / sizeof(processes[0]);
    printf("Process Tree:\n");
    displayProcessTree(processes, n, 0, 1);
    return 0;
}
