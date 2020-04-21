// PROGRAMA p02.c 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h> 

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;  // mutex p/a sec.critica 
#define STDERR 2 
#define NUMITER 10000 
int N=50000;

void * thrfunc(void * arg) {   
    void *ret;
    int count=0;
    ret=malloc(sizeof(int));
    fprintf(stderr, "Starting thread %s\n", (char *) arg);   
    
    while(N>0) {
        pthread_mutex_lock(&mut);
        count++;
        N--; 
        pthread_mutex_unlock(&mut);
        write(STDERR,arg,1);  
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
      
      

    fprintf(stderr,"\nta wrote %d numbers\n",*(int *)ra);
    fprintf(stderr,"\ntb wrote %d numbers\n",*(int *)rb);
    fprintf(stderr,"\nTotal: %d\n",*(int *)ra+*(int *)rb);

    return 0; 
} 