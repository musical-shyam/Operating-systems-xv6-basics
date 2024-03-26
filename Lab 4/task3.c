#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define INPUT_FILE "./if1"
#define OUTPUT_FILE "./result"

int main(int argc, char * argv[]) {
    pid_t pid;
	pid = fork();
	if (pid == -1) { 
		fprintf(stderr, "fork failed\n"); 
	} 
	if (pid == 0) { 
		printf("IN CHILD: pid=%d\n",getpid());
        int input_fd = open(INPUT_FILE, O_RDONLY);
        if (input_fd == -1) {
            perror("Failed to open input file");
            exit(1);
        }
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
        close(STDOUT_FILENO);
        open(OUTPUT_FILE, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

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
    execlp("dup2", "dup2",INPUT_FILE, "result", NULL);
	} 
    return 0;
}
