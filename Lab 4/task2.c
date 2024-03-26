#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char * argv[]) {
    pid_t pid;
	pid = fork();
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
	} 
	if (pid == 0) { 
		printf("IN CHILD: pid=%d\n",getpid());
        if (argc > 1) {
        execvp(argv[1], &argv[1]);
        // If execvp returns, it must have failed
        printf("Command %s does not exist.\n", argv[1]);
        exit(1);
        }
	} 
	if (pid > 0) { 
    wait(NULL);
	printf("IN PARENT: successfully waited child (pid=%d)\n", pid); 
	} 
    return 0;
}
