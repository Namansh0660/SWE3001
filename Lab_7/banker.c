#include<stdio.h>
#include<stdbool.h>

int main() {
    // Initial allocation and maximum requirement of each student
    int allocation[5][3] = {{1, 1, 2}, {2, 1, 2}, {3, 0, 1}, {0, 2, 0}, {1, 1, 2}};
    int max[5][3] = {{5, 4, 4}, {4, 3, 3}, {9, 1, 3}, {8, 6, 4}, {2, 2, 3}};
    int available[3] = {10, 7, 8}; // Available quantities of components A, B, C

    int need[5][3]; // Need matrix
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    bool finish[5] = {false}; // To track if a student is finished or not
    int safeSeq[5], work[3], count = 0;

    // Copy the available vector to the work vector
    for(int i = 0; i < 3; i++) {
        work[i] = available[i];
    }

    while(count < 5) {
        bool found = false;
        for(int i = 0; i < 5; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < 3; j++) {
                    if(need[i][j] > work[j])
                        break;
                }
                if(j == 3) {
                    for(int k = 0; k < 3; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if(!found) {
            printf("System is not in a safe state.\n");
            return -1;
        }
    }

    printf("1. Need Matrix:\n");
    for(int i = 0; i < 5; i++) {
        printf("S%d: %d %d %d\n", i, need[i][0], need[i][1], need[i][2]);
    }

    printf("\n2. Available Vector:\n");
    printf("%d %d %d\n", work[0], work[1], work[2]);

    printf("\n3. Safe Sequence:\n");
    for(int i = 0; i < 5; i++) {
        printf("S%d ", safeSeq[i]);
    }
    printf("\n");

    return 0;
}
