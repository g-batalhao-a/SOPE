// PROGRAMA p04.c 
#include <stdio.h> 
#include <stdlib.h> 
#include<unistd.h> 
#include<fcntl.h>// For O_* constants 
#include<sys/mman.h> 
#include<sys/types.h> 
#include <semaphore.h>

#define MAXELEMS 10000000 // nr. max de posicoes 
#define MAXTHREADS 100    // nr. max de threads 
#define min(a, b) (a)<(b)?(a):(b) 
#define SHM_SIZE 10

int npos; 
int buf[MAXELEMS], pos=0, val=0;                // variaveis partilhadas 

char SEM_NAME[]="/sem1";
char SHM_NAME[]="/shm1";

void *fill(void *nr) {         
    while (1) {                 
        pthread_mutex_lock(&mut);                 
        if (pos >= npos) {                         
            pthread_mutex_unlock(&mut);                         
            return NULL;                 
        }                 
        buf[pos] = val;                 
        pos++; 
        val++;                 
        pthread_mutex_unlock(&mut);                 
        *(int *)nr += 1;         
    } 
} 

void *verify(void *arg) {         
    int k;         
    for (k=0; k<npos; k++)                 
        if (buf[k] != k)   // detecta valores errados                         
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);         
    
    return NULL; 
} 

int main(int argc, char *argv[]) {         
    int k, nthr, count[MAXTHREADS];   // array para contagens          
    pthread_t tidf[MAXTHREADS], tidv; // tids dos threads         
    int total;         
    int shmfd;
    char*shm,*s;
    sem_t *sem;
    pid_t pid;
    if (argc != 3) {                 
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);                 
        return 1;         
    }
    pid=fork();
    
    if(pid!=0){
        //Creating shared memory region
        shmfd=shm_open(SHM_NAME,O_CREAT|O_RDWR,0600);
        if(shmfd<0){
            perror("WRITER failure in shm_open()\n");
            exit(1);
        }
        if(ftruncate(shmfd,SHM_SIZE)<0){
            perror("WRITER failure in ftruncate()\n");
            exit(2);
        }
        //attach to virtual memory
        shm=(char *)mmap(0,SHM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
        if(shm==MSP_FAILED){
            perror("WRITER failure in mmap()\n");
            exit(3);
        }

        //create & initialize semaphore
        sem=sem_open(SEM_NAME,O_CREAT,0600,0);
        if(sem==SEM_FAILED){
            perror("WRITER failure in sem_open()\n");
            exit(4);
        }

        //write into shared memory region
        npos = min(atoi(argv[1]), MAXELEMS);    //no. efectivo de posicoes         
        nthr = min(atoi(argv[2]), MAXTHREADS);  //no. efectivo de threads
    }
    

    for (k=0; k<nthr; k++) {   // criacao das threads 'fill'                 
        count[k] = 0;                 
        pthread_create(&tidf[k], NULL, fill, &count[k]);         
    }         
    
    total=0;         
    for (k=0; k<nthr; k++) {   //espera threads 'fill'                 
        pthread_join(tidf[k], NULL);                    
        printf("count[%d] = %d\n", k, count[k]);                 
        total += count[k];          
    }         
    printf("total count = %d\n",total);   // mostra total         
    
    pthread_create(&tidv, NULL, verify, NULL);          
    pthread_join(tidv, NULL);   // espera thread 'verify'          
    return 0; 
}