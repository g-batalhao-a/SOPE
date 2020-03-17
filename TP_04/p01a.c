// PROGRAMA p01a.c 
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
void sigint_handler(int signo) {   
    printf("In SIGINT handler ...\n"); 
} 

int main(void) {   
    struct sigaction action;
    action.sa_handler=sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;

    if (sigaction(SIGINT,&action,NULL) < 0)   {     
        fprintf(stderr,"Unable to install SIGINT handler\n");     
        exit(1);   
    }   

    if(signal(SIGTERM,sigint_handler)<0||signal(SIGUSR1,SIG_IGN)<0||signal(SIGUSR2,SIG_IGN)<0){
        fprintf(stderr,"Can't ignore signals\n");
    }
    printf("Sleeping for 30 seconds ...\n");   
    int time_left=sleep(30);

    while(time_left!=0){time_left=sleep(time_left);}

    printf("Waking up ...\n");   
    exit(0); 
} 