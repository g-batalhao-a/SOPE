// PROGRAMA p06.c 
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define NUM_THREADS 10
#include <unistd.h> 
#include <sys/file.h> 
#include <string.h> 
#define MAX_MSG_LEN 20 
int main(int argc, char *argv[]) { 
    int   fd, opcode; 
    if (argc!=2 && argc!=3) {   
        printf("Usage: cli_03 <opcode> <username> OR cli_03 0\n");   
        exit(1);  
    }  
    
    fd=open("/tmp/requests",O_WRONLY); 
    if (fd == -1) {   
        printf("Oops !!! Service is closed !!!\n");   
        exit(1); 
    }  
    printf("FIFO 'requests' openned in WRITEONLY mode\n");  
    opcode=atoi(argv[1]);  
    write(fd,&opcode,sizeof(int)); 
    if (opcode!=0) {   
        write(fd,argv[2],strlen(argv[2])+1);  
    }  close(fd); 
    return 0; 
} 
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