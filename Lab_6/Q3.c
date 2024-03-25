#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef enum { THINKING, HUNGRY, EATING } state_t;

pthread_mutex_t monitor_mutex;
pthread_cond_t cond_vars[NUM_PHILOSOPHERS];
state_t philosophers[NUM_PHILOSOPHERS];

void test(int phil_id) {
    if (philosophers[phil_id] == HUNGRY &&
        philosophers[(phil_id + 1) % NUM_PHILOSOPHERS] != EATING &&
        philosophers[(phil_id + 4) % NUM_PHILOSOPHERS] != EATING) {
        philosophers[phil_id] = EATING;
        printf("Philosopher %d is eating\n", phil_id);
        pthread_cond_signal(&cond_vars[phil_id]);
    }
}

void take_forks(int phil_id) {
    pthread_mutex_lock(&monitor_mutex);
    philosophers[phil_id] = HUNGRY;
    printf("Philosopher %d is hungry\n", phil_id);
    test(phil_id);
    if (philosophers[phil_id] != EATING) {
        pthread_cond_wait(&cond_vars[phil_id], &monitor_mutex);
    }
    pthread_mutex_unlock(&monitor_mutex);
}

void put_forks(int phil_id) {
    pthread_mutex_lock(&monitor_mutex);
    philosophers[phil_id] = THINKING;
    printf("Philosopher %d is thinking\n", phil_id);
    test((phil_id + 1) % NUM_PHILOSOPHERS);
    test((phil_id + 4) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&monitor_mutex);
}

void *philosopher(void *arg) {
    int phil_id = *((int *)arg);

    while (1) {
        sleep(rand() % 3 + 1);
        take_forks(phil_id);
        sleep(rand() % 3 + 1);
        put_forks(phil_id);
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int phil_ids[NUM_PHILOSOPHERS];

    pthread_mutex_init(&monitor_mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&cond_vars[i], NULL);
        phil_ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &phil_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
        pthread_cond_destroy(&cond_vars[i]);
    }

    pthread_mutex_destroy(&monitor_mutex);

    return 0;
}
