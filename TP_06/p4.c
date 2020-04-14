// PROGRAMA p04.c 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#define NUM_THREADS 10 

void *PrintHello(void *threadnum) {    
    //printf("Hello from thread TID: %ld!\n", pthread_self());
    sleep(1);    
    return threadnum; 
} 

int main() {    
    pthread_t threads[NUM_THREADS];    
    int t;    
    int *thrarg[NUM_THREADS];
    void *r;
    for(t=0; t< NUM_THREADS; t++){    
        thrarg[t]=(int *)malloc(sizeof(int));
        *thrarg[t]=t;   
        printf("Creating thread %d\n", t);       
        pthread_create(&threads[t], NULL, PrintHello, thrarg[t]);
        pthread_join(threads[t],&r);
        printf("Hello from thread TID: %d!\n", *(int *)r);    
    }    
    pthread_exit(0); 
}