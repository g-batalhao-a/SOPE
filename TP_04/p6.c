// PROGRAMA p6.c
#include <string.h>
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h>

int delay;
void alarm_handler(int signo){
    int status;
    pid_t pid;

    pid=wait(&status);
    printf("Child %d terminated with %d seconds\n",pid,delay);
    exit(0);
}

int main(int argc, char *argv[]){
    pid_t pid;

    signal(SIGALRM, alarm_handler);
    pid=fork();

    if(argc<3){
        printf("usage: %s time prog prog_args\n",argv[0]);      
        exit(1); 
    }
    
    if(pid==0){
        
        execvp(argv[2],&argv[2]);
    }
    else{
        sscanf(argv[1],"%d",&delay);
        alarm(delay);
        wait(&delay);
        printf("Program %s exceeded limit of %d seconds\n",argv[2],delay);
        kill(pid,SIGKILL);
    }
    
    return 0;
}