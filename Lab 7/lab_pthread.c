#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Compile with "-lpthread"

int total = 0; // to record total number of messages from the two threads
int total_counter = 0;
pthread_t t1, t2;
void * thread_work(void * arg) {
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    long self_counter = 0; // to record how many times printed by the current thread
    char **input = (char **)arg;
    pthread_t self = pthread_self();
    int count;
    for (count = 1; input[count] != NULL; count++); 
    while(total_counter < total){
        pthread_mutex_lock(&lock);
        total_counter++;
        pthread_mutex_unlock(&lock);
        
        if (pthread_equal(t1,self)){
            printf("%d: In thread 1 (TID=%lu): ",total_counter, self);
            self_counter++;
            for (int i = 0; input[i]!=NULL;i++){
                printf("%s ", input[i]);
            }
        }
        else if (pthread_equal(t2,self)){
            printf("%d: In thread 2 (TID=%lu): ",total_counter, self);
            self_counter++;
            for (int i = count - 1 ; i>=0;i--){
                printf("%s ", input[i]);
            }
        }
        printf("\n");
        fflush(stdout);
        if(total_counter >= total){
            break;
        }
    }
    return (void *)self_counter;
}

int main(int argc, char * argv[]) {
    long t1_c = 0, t2_c = 0; // to record numbers of times printed by T1 and T2

    if (argc < 3) {
        printf("There must be 2 arguements following the binary!\n");
        return 0;
    }

    total = atoi(argv[1]); 
    
    pthread_create(&t1, NULL, thread_work, argv + 2);
    pthread_create(&t2, NULL, thread_work, argv + 2);
    pthread_join(t1, (void *)&t1_c);
    pthread_join(t2, (void *)&t2_c);
    
    printf("In main thread: T1 printed %ld times. T2 printed %ld times.\n", t1_c, t2_c);
    
    return 0;
}


