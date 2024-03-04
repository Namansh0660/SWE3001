//1 Assume that the parent process and child process shares the same common variable. 
/*    Print the value of common variable before the forthest is called.The parent process modifies values of c     ommon variable which is unaware to the child process.
    Write separate functions for parent process and child process using c program*/
    
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int common_var = 0;

void parentProcess() {
    common_var++;
    printf("Parent Process PID : %d\n",getppid());
    printf("common variable value in Parent Process = %d\n\n", common_var);
}

void childProcess() {
    printf("Child Process PID : %d\n",getpid());
    printf("common variable value in Child Process = %d\n", common_var);
}

int main() {
    pid_t pid = fork();
    
    printf("Initial Common Variable = %d\n",common_var);

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        childProcess();
    } else {
        // Parent process
        parentProcess();
    }

    return 0;
}
    
