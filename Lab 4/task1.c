#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
	pid = fork();
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
	} 
	if (pid == 0) { 
		printf("IN CHILD: pid=%d\n",getpid()); 
        execlp("ls", "ls","-l", "-a", NULL);
        // If execlp returns, it must have failed
        exit(1);
    
	} 
	if (pid > 0) { 
    wait(NULL);
	printf("IN PARENT: successfully waited child (pid=%d)\n", pid); 
	} 
}
