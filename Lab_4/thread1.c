#include <stdio.h>
#include <pthread.h>
void *check_odd_even(void *arg) {
    int num = *((int*)arg);
    if (num % 2 == 0) {
        printf("Thread ID: %ld - %d is even.\n", pthread_self(), num);
    } else {
        printf("Thread ID: %ld - %d is odd.\n", pthread_self(), num);
    }
    pthread_exit(NULL);
}

void *check_prime(void *arg) {
    int num = *((int*)arg);
    int flag = 0;
    for (int i = 2; i <= num / 2; ++i) {
        if (num % i == 0) {
            flag = 1;
            break;
        }
    }
    if (num <= 1 || flag == 1) {
        printf("Thread ID: %ld - %d is not a prime number.\n", pthread_self(), num);
    } else {
        printf("Thread ID: %ld - %d is a prime number.\n", pthread_self(), num);
    }
    pthread_exit(NULL);
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    pthread_t tid1, tid2;

    // Create first thread to check odd/even
    pthread_create(&tid1, NULL, check_odd_even, &num);
    
    // Create second thread to check prime
    pthread_create(&tid2, NULL, check_prime, &num);
    
    // Wait for both threads to finish
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
