#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    pid_t pid = fork();
    
    int common_variable;
    
    if (pid==0) {
        printf("This is the Child process and pid is: %d\n",getpid());
        printf("This is the Parent process id of Child Process : %d\n",getppid());
        common_variable = 1;
        printf("Value of common variable in Child Process = %d\n",common_variable);
        exit(0);
        
    } else if (pid > 0) {
        printf("This is the Parent process and pid is: %d\n",getpid());
        common_variable = 0;
        printf("Value of common variable in Parent Process = %d\n",common_variable);
    } else {
        printf("Error while forking\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}







corrected one
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int common_variable = 0;

void parentProcess() {
    common_variable = 10;
    printf("Parent process - common variable value: %d\n", common_variable);
}

void childProcess() {
    printf("Child process - common variable value: %d\n", common_variable);
}

int main() {
    pid_t pid = fork();

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
