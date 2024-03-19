#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_THREADS 2

bool want[NUM_THREADS] = {false, false};
int turn = 0;
int balance = 0;

void lock(int thread_id) {
    int other = 1 - thread_id;
    want[thread_id] = true;
    turn = thread_id;
    while (want[other] && turn == thread_id) {
        // Wait until it's this thread's turn
    }
}

void unlock(int thread_id) {
    want[thread_id] = false;
}

void* deposit(void* arg) {
    int amount = *((int*)arg);
    lock(0);  // Assuming thread 0 represents person X
    balance += amount;
    printf("Person X deposited Rs.%d. New balance: Rs.%d\n", amount, balance);
    unlock(0);
    pthread_exit(NULL);
}

void* withdraw(void* arg) {
    int amount = *((int*)arg);
    lock(1);  // Assuming thread 1 represents person Y
    if (balance >= amount) {
        balance -= amount;
        printf("Person Y withdrew Rs.%d. New balance: Rs.%d\n", amount, balance);
    } else {
        printf("Insufficient funds for withdrawal.\n");
    }
    unlock(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int x_deposit = 1000;
    int y_withdraw = 500;

    pthread_create(&threads[0], NULL, deposit, (void*)&x_deposit);
    pthread_create(&threads[1], NULL, withdraw, (void*)&y_withdraw);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final balance: Rs.%d\n", balance);

    return 0;
}
