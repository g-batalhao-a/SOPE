// PROGRAMA p01.c 
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h> 

#define STDERR 2 
#define NUMITER 10000 

void * thrfunc(void * arg) {   
    int i;   
    int value;
    value = *(int *) arg;
    char tmp=value+'0';
    fprintf(stderr, "Starting thread %d\n", value);//fprintf(stderr, "Starting thread %s\n", (char *) arg);   
    for (i = 1; i <= NUMITER; i++) write(STDERR,&tmp,1);//write(STDERR,arg,1);   
    return NULL; 
} 

int main() {    
    pthread_t ta, tb; 
    int a=1,b=2;
    char a1='1',b1='2';
    pthread_create(&ta, NULL, thrfunc, &a);   
    pthread_create(&tb, NULL, thrfunc, &b);   

    pthread_join(ta, NULL);   
    pthread_join(tb, NULL);   

    return 0; 
} 