#include <stdio.h>
#include <unistd.h>
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
void my_signal_handler(int signum) {
    printf("\nCaught SIGINT (%d). Exiting safely...\n", signum);
    _exit(signum);
}

int main() {
    signal(SIGINT, my_signal_handler);

    while (1) {
        printf("Running... Press Ctrl-C to stop.\n");
        sleep(1); 
    }
    return 0;
}