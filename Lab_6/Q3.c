#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_ITERATIONS 10

typedef enum { THINKING, HUNGRY, EATING } PhilosopherState;

pthread_mutex_t mutex;
pthread_cond_t cond_vars[NUM_PHILOSOPHERS];
PhilosopherState states[NUM_PHILOSOPHERS];
int iterations = 0;

void monitor_init() {
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&cond_vars[i], NULL);
        states[i] = THINKING;
    }
}

void monitor_take_forks(int philosopher_id) {
    pthread_mutex_lock(&mutex);
    states[philosopher_id] = HUNGRY;
    while ((states[(philosopher_id + 1) % NUM_PHILOSOPHERS] == EATING) ||
           (states[(philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] == EATING)) {
        pthread_cond_wait(&cond_vars[philosopher_id], &mutex);
    }
    states[philosopher_id] = EATING;
    pthread_mutex_unlock(&mutex);
}

void monitor_put_forks(int philosopher_id) {
    pthread_mutex_lock(&mutex);
    states[philosopher_id] = THINKING;
    pthread_cond_signal(&cond_vars[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
    pthread_cond_signal(&cond_vars[(philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS]);
    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* arg) {
    int philosopher_id = *((int*)arg);

    while (iterations < NUM_ITERATIONS) {
        // Think
        usleep(rand() % 1000);

        // Pick up forks
        monitor_take_forks(philosopher_id);
        printf("Philosopher %d is eating\n", philosopher_id);
        usleep(rand() % 1000);

        // Put down forks
        monitor_put_forks(philosopher_id);
        printf("Philosopher %d is thinking\n", philosopher_id);

        iterations++;
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    monitor_init();

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_destroy(&cond_vars[i]);
    }

    return 0;
}





/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5 // Number of philosophers

enum { THINKING, HUNGRY, EATING } state[N]; // States of philosophers
sem_t mutex; // Mutex for critical sections
sem_t forks[N]; // Semaphores for each fork

void *philosopher(void *arg) {
    int phil_id = *((int *)arg);
    while (1) {
        printf("Philosopher %d is thinking\n", phil_id);

        // Start critical section (acquire mutex)
        sem_wait(&mutex);
        state[phil_id] = HUNGRY;
        printf("Philosopher %d is hungry\n", phil_id);
        // Try to acquire left fork
        sem_wait(&forks[phil_id]);
        // Try to acquire right fork
        sem_wait(&forks[(phil_id + 1) % N]);
        state[phil_id] = EATING;
        printf("Philosopher %d is eating\n", phil_id);
        // End critical section (release mutex)
        sem_post(&mutex);

        sleep(rand() % 3 + 1); // Simulate eating time

        // Start critical section (acquire mutex)
        sem_wait(&mutex);
        state[phil_id] = THINKING;
        printf("Philosopher %d finished eating and is thinking\n", phil_id);
        // Release left fork
        sem_post(&forks[phil_id]);
        // Release right fork
        sem_post(&forks[(phil_id + 1) % N]);
        // End critical section (release mutex)
        sem_post(&mutex);

        sleep(rand() % 3 + 1); // Simulate thinking time
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[N];
    int phil_ids[N];
    srand(time(NULL)); // Initialize random seed

    sem_init(&mutex, 0, 1); // Initialize mutex
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1); // Initialize forks
        phil_ids[i] = i;
    }

    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&phil_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&mutex); // Destroy mutex
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]); // Destroy forks
    }

    return 0;
}

*/
