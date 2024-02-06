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
