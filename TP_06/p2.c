// PROGRAMA p02.c 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h> 

#define STDERR 2 
#define NUMITER 10000 
int N=50000;

void * thrfunc(void * arg) {   
    void *ret;
    int i;
    int count=0;
    ret=malloc(sizeof(int));
    fprintf(stderr, "Starting thread %s\n", (char *) arg);   
    while(N>0) {
        write(STDERR,arg,1);  
        count++;
        N--;
    }
    *(int *)ret=count;
    return ret; 
} 

int main() {    
    pthread_t ta, tb; 
    void *ra,*rb ;

    pthread_create(&ta, NULL, thrfunc, "1");   
    pthread_create(&tb, NULL, thrfunc, "2");   

    pthread_join(ta, &ra);   
    pthread_join(tb, &rb);   

    printf("\nta wrote %d numbers\n",*(int *)ra);
    printf("\ntb wrote %d numbers\n",*(int *)rb);

    return 0; 
} 