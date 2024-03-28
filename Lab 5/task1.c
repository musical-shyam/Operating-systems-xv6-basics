#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    char * argv1[] = {"cat", "Makefile", 0};
    //char * argv2[] = {"head", "-4", 0};
    char * argv2[] = {"wc", "-l", 0};
    setbuf(stdout, NULL);
    int pfds[2]; 
    pid_t c1_pid, c2_pid;

    // creating a pipe
    if (pipe(pfds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }             
    // creating first child which executes cat                                      
    c1_pid = fork();                      
    if (c1_pid == 0 ) {  
        printf("In CHILD-1 (PID = %d): executing command %s ...\n",  getpid(), argv1[0]);                                  
        close(pfds[0]);         
        // associating write side of pipe with the STDOUT of Child 1
        dup2(pfds[1],STDOUT_FILENO);
        //closing the write side of the pipe
        close(pfds[1]);
        //exectuting cat
        execvp(argv1[0],argv1);                    
    } 
    else{
        //creating the second child which executes head or wc
        c2_pid = fork();
        if (c2_pid == 0 ){    
            printf("In CHILD-2 (PID = %d): executing command %s ...\n", getpid(), argv2[0]);                                      
            close(pfds[1]);   
            // associating read side of pipe with the STDIN of Child 2
            dup2(pfds[0],STDIN_FILENO);  
            //closing the read side of the pipe 
            close(pfds[0]);  
            //exectuting head or wc                                 
            execvp(argv2[0], argv2);      
        }
        // closing the unused sides of the pipe in the parent
        close(pfds[0]);
        close(pfds[1]);
        // waiting for the both the child processes to complete
        waitpid(c2_pid,NULL,0); 
        waitpid(c1_pid,NULL,0);
        printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c1_pid);
        printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c2_pid);

    }



    return 0;
}
