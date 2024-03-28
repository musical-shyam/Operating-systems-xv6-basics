#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    char * argv1[] = {"cat", "Makefile", 0};
    char * argv2[] = {"head", "-4", 0};
    char * argv3[] = {"wc", "-l", 0};

    setbuf(stdout, NULL);

    int pipe1[2];
    int pipe2[2];

    //creating pipe 1
    if (pipe(pipe1) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    // creating first child which executes cat  
    pid_t c1_pid = fork();
    if (c1_pid == 0) {
        printf("In CHILD-1 (PID = %d): executing command %s ...\n",  getpid(), argv1[0]);   
        // associating write side of pipe 1 with the STDOUT of Child 1
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe1[1]);
        execvp(argv1[0], argv1);

    }
    //creating pipe 2
    if (pipe(pipe2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }
    // creating first child which executes cat  
    pid_t c2_pid = fork();
    if (c2_pid == 0) {
        printf("In CHILD-2 (PID = %d): executing command %s ...\n", getpid(), argv2[0]); 
        // associating read side of pipe 1 with the STDIN of Child 2
        dup2(pipe1[0], STDIN_FILENO);
        // associating write side of pipe 2 with the STDOUT of Child 2
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[1]);
        close(pipe1[0]);
        close(pipe2[0]);
        close(pipe2[1]);
        execvp(argv2[0], argv2);
        
    }

    pid_t c3_pid = fork();
    if (c3_pid == 0) {
        printf("In CHILD-3 (PID = %d): executing command %s ...\n", getpid(), argv3[0]); 
        // associating read side of pipe 2 with the STDIN of Child 3
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[1]);
        close(pipe2[0]);
        close(pipe1[0]);
        close(pipe1[1]);
        execvp(argv3[0], argv3);
        
    }
    // closing the unused sides of the pipe in the parent
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);
    // waiting for the child processes to complete
    waitpid(c3_pid, NULL, 0);
    waitpid(c2_pid, NULL, 0);
    waitpid(c1_pid, NULL, 0);
    printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c1_pid);
    printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c2_pid);
    printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c3_pid);
    return 0;
}
