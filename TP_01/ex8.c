// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <sys/times.h>
#include <unistd.h>
int main(int argc, char* argv[]){
    clock_t start,end;
    double cpu_time_used;
    struct tms buf;
    start=clock();
    srand(time(0));
    int generated_number;
    int iteration=0;
    do{
        iteration++;
        generated_number = rand()%atoi(argv[1]);
        printf("Iteration %d: %d\n",iteration,generated_number);
    }while(generated_number!=atoi(argv[2]));
    sleep(5);
    times(&buf);
    end=clock();
    cpu_time_used = ((double)(end-start))/CLOCKS_PER_SEC;
    printf("real: %f s\n",cpu_time_used);
    printf("user: %f s\n",(double)(buf.tms_utime/CLOCKS_PER_SEC));

    printf("sys: %f s\n",(double)(buf.tms_stime/CLOCKS_PER_SEC));
    exit(0);  // zero é geralmente indicativo de "sucesso" 
} 