//Author: Jayson Boubin -- Fall 2022
#include "matmul.h"

int* mat1 = NULL;
int* mat2 = NULL;
int* matRes = NULL;
int* matSol = NULL;

void multiply() {
    //TODO
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            matRes[i*K + j] = 0; // Initializing array element to zero
            for (int k = 0; k < N; k++) {
                matRes[i*K + j] += mat1[i*N + k] * mat2[k*K + j]; //multiplication for each result element
            }
        }
    }
    //printMats();
}

void *thread_multiply(void *arg) {
    threadargs *args = (threadargs *)arg;
    int tot = M * K; // Total elements in the result matrix

    // Each thread starts at its thread id and jumps forward by the total number of threads
    for (int idx = args->tid; idx < tot; idx += args->totalThreads) {
        int i = idx / K; // Converting index to 2D row
        int j = idx % K; // Converting index to 2D column
        matRes[i * K + j] = 0; // Initialize element
        for (int k = 0; k < N; k++) {
            matRes[i * K + j] += mat1[i * N + k] * mat2[k * K + j];// multiplication line
        }
    }
    
    return NULL;
}

void multiplyWithThreads(int nThreads){
    //TODO
    int minDim = M < N ? (M < K ? M : K) : (N < K ? N : K); // Finding the minimum of M, N, K
    int maxThreads = nThreads > minDim ? minDim : nThreads; // Limiting threads to minimum dimension
    pthread_t threads[maxThreads];
    threadargs args[maxThreads];

    for (int i = 0; i < maxThreads; i++) {
        args[i].tid = i; //allocating thread number
        args[i].totalThreads = maxThreads; //allocating the total no of threads created
        pthread_create(&threads[i], NULL, thread_multiply, (void *)&args[i]); //starting threads and making it multiply
    }

    for (int i = 0; i < maxThreads; i++) {
        pthread_join(threads[i], NULL);// joining all the multiplications
    }
    //printMats();
}

//--- DO NOT MODIFY BELOW HERE ---
int main(int argc, char* argv[])
{
    
    struct timeval start, end;
    double mult_time;

    if(argc != 2) {
        printf("Please provide 1 argument: #threads (int)\n");
        exit(-1);
    }

    int nthreads = atoi(argv[1]);
    
    if(nthreads <= 0){
        printf("Please enter a correct value for #threads\n");
        exit(-1);
    }
    printf("--- Reading in Matrices ---\n");

    mat1 = initialize(M, N, MAT_A);
    mat2 = initialize(N, K, MAT_B);
    matSol = initialize(M, K, MAT_C);
    matRes = malloc(M * K * sizeof(int)); 

    printf("--- Matrices Successfully Read, Multiplying Now ---\n");

    gettimeofday(&start, NULL);
    if(nthreads > 1){
        printf("--- Multiplying with %d threads ---\n", nthreads);
        multiplyWithThreads(nthreads);
    } else {
        printf("--- Multiplying with a single thread ---\n");
        multiply();
    }
    
    gettimeofday(&end, NULL); 
    mult_time = getTotalTime(start, end);

    if(compare()){
        printf("Correct! Your matrices multiplied properly\n");
    } else {
        printf("Incorrect! Your matrices did not multiply properly. Check your solution and try again.\n");
    }
    
    printf("This operation took %f seconds\n", mult_time);

    //Don't forget to free allocated heap memory!
    
    free(mat1);
    free(mat2);
    free(matRes);
    free(matSol);
    
    return 0;
}
