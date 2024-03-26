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
    pipe(pfds);                                                    
    (c1_pid = fork());            
                                     
    if (c1_pid == 0 ) {  
        printf("In CHILD-1 (PID = %d): executing command %s ...\n",  getpid(), argv1[0]);                                         
        close(pfds[0]);         
        dup2(pfds[1],STDOUT_FILENO);
        execvp(argv1[0],argv1);                    
    } 
    else{
        (c2_pid = fork());
        if (c2_pid == 0 ){    
             printf("In CHILD-2 (PID = %d): executing command %s ...\n", getpid, argv2[0]);                                      
            close(pfds[1]);   
            dup2(pfds[0],STDIN_FILENO);                                      
            execvp(argv2[0], argv2);      
        }
        waitpid(c2_pid,NULL,0); 
        waitpid(c1_pid,NULL,0);
        printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c1_pid);
        printf("Parent(PID = %d): successfully reaped child (PID = %d) \n", getppid(), c2_pid);

    }



    return 0;
}
