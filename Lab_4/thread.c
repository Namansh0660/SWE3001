#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Function executed by the first thread
void *threadFunction1(void *arg) {
    printf("Thread 1 is executing\n");
    sleep(2); // Simulating some task
    printf("Thread 1 is terminating\n");
    pthread_exit(NULL);
}

// Function executed by the second thread
void *threadFunction2(void *arg) {
    printf("Thread 2 is executing\n");
    sleep(3); // Simulating some task
    printf("Thread 2 is terminating\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2; // Thread IDs

    // Creating first thread
    if (pthread_create(&tid1, NULL, threadFunction1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Creating second thread
    if (pthread_create(&tid2, NULL, threadFunction2, NULL) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Waiting for threads to finish execution
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("Both threads have terminated\n");

    return 0;
}
