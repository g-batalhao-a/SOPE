// PROGRAMA p03.c 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define NUM_THREADS 10 
void *PrintHello(void *threadnum) {    
    printf("Hello from thread no. %d!\n", *(int *) threadnum);    
    pthread_exit(NULL); 
} 

int main() {    
    pthread_t threads[NUM_THREADS];    
    int t;    
    int *thrarg[NUM_THREADS];
    
    for(t=0; t< NUM_THREADS; t++){    
        thrarg[t]=(int *)malloc(sizeof(int));
        *thrarg[t]=t;   
        printf("Creating thread %d\n", t);       
        pthread_create(&threads[t], NULL, PrintHello, thrarg[t]);    
    }    
    pthread_exit(0); 
}