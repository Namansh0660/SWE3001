#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 4
#define NUM_WRITERS 1

sem_t mutex, wrt;
int read_count = 0;

void *reader(void *arg) {
    int id = *((int *)arg);

    while (1) {
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Reading the file (critical section for reading)
        printf("Reader %d is reading the file\n", id);
        sleep(1); // Simulating reading process

        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        sleep(2); // Reader's waiting time before accessing the file again
    }
}

void *writer(void *arg) {
    int id = *((int *)arg);

    while (1) {
        sem_wait(&wrt);

        // Writing to the file (critical section for writing)
        printf("Writer %d is updating the file\n", id);
        sleep(2); // Simulating writing process

        sem_post(&wrt);

        sleep(3); // Writer's waiting time before accessing the file again
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
