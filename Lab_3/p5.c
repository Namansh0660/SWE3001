/*
An orphan process is a child process whose parent terminates before the child. The orphan process is then adopted by the init process (with PID 1).
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;

    // Create the first child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid > 0) {
        // Parent process
        printf("Parent Process (PID %d) with Parent (PPID %d)\n", getpid(), getppid());
        sleep(2);  // Allow time for child to become orphan

        // The parent process terminates, creating an orphan child
        printf("Parent Process (PID %d) terminating\n", getpid());
    } else {
        // Child process
        printf("Child Process (PID %d) with Parent (PPID %d)\n", getpid(), getppid());

        // Simulate some work in the child process
        sleep(6);

        // The child process terminates
        printf("Child Process (PID %d) terminating\n", getpid());
        printf("Child Process (PID %d) with Parent (PPID %d)\n", getpid(), getppid());

    }

    return 0;
}
