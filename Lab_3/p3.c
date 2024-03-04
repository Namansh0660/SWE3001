/*
write a c program to illustrate process termination. 
    Create 5 processes among which one is the parent process and 4 child processes terminate all processes in the sequence given below : 
    (i) The parent process should terminate last after all the child processes 
    (ii) The fourth child process should terminate before the parent process. 
    (iii) The first child process terminates after the third child process. 
    (iv) The second child process should terminate before the first child process and after the third process 
    (v) The third child process should terminate first. 
    Print the termination in the sequence along with the ID of each process.
    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void terminate(int id) {
    printf("Process %d terminated\n", id);
}

int main() {
    printf("Parent process ID: %d\n", getpid());

    // Creating the third child process (first to terminate)
    pid_t pid3 = fork();
    if (pid3 == 0) {
        // Third child process code
        terminate(3);
        exit(0);
    }

    // Creating the second child process (second to terminate)
    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Second child process code
        waitpid(pid3, NULL, 0); // Wait for the third child process to terminate
        terminate(2);
        exit(0);
    }

    // Creating the first child process (third to terminate)
    pid_t pid1 = fork();
    if (pid1 == 0) {
        // First child process code
        terminate(1);
        exit(0);
    }

    // Creating the fourth child process (fourth to terminate)
    pid_t pid4 = fork();
    if (pid4 == 0) {
        // Fourth child process code
        waitpid(pid1, NULL, 0); // Waiting for the first child process to terminate
        terminate(4);
        exit(0);
    }

    // Parent process code
    waitpid(pid4, NULL, 0); // Waiting for the fourth child process to terminate
    terminate(getpid());

    return 0;
}
