#include <stdio.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int turn;
int flag[2] = {FALSE, FALSE};
int balance = 0;

void* deposit(void* arg) {
    int amount = *((int*) arg);
    int id = 0; // ID for person X

    flag[id] = TRUE;
    turn = 1 - id;

    while (flag[1 - id] && turn == 1 - id) {
        // Wait until it's safe to deposit
    }

    // Critical section (deposit)
    balance += amount;
    printf("Person X deposited Rs. %d. Current balance: Rs. %d\n", amount, balance);

    flag[id] = FALSE;

    return NULL;
}

void* withdraw(void* arg) {
    int amount = *((int*) arg);
    int id = 1; // ID for person Y

    flag[id] = TRUE;
    turn = 1 - id;

    while (flag[1 - id] && turn == 1 - id) {
        // Wait until it's safe to withdraw
    }

    // Critical section (withdraw)
    if (balance >= amount) {
        balance -= amount;
        printf("Person Y withdrew Rs. %d. Current balance: Rs. %d\n", amount, balance);
    } else {
        printf("Insufficient balance. Withdrawal canceled.\n");
    }

    flag[id] = FALSE;

    return NULL;
}

int main() {
    pthread_t tid[2];
    int depositAmount = 1000;
    int withdrawAmount = 500;

    pthread_create(&tid[0], NULL, deposit, &depositAmount);
    pthread_create(&tid[1], NULL, withdraw, &withdrawAmount);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    return 0;
}
