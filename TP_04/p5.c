// PROGRAMA p04a.c
#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h>

void sigchld_handler(int signo) {   
    printf("Entering SIGINT handler ...\n");   
    pid_t pid;
    int status;
    while((pid = waitpid(0, &status, WNOHANG)) > 0);
    printf("Exiting SIGINT handler ...\n");  
}

int main(void) {   
    pid_t pid;   
    int i, n, status;

    struct sigaction action;  
    action.sa_handler=sigchld_handler;
    //action.sa_handler = SIG_IGN;  //handle signal by ignoring
    sigemptyset(&action.sa_mask);  
    action.sa_flags = 0;    

    if(sigaction(SIGCHLD, &action,0)<0){
        printf("Couldn't implement SIGCHLD ignore\n");
        exit(1);
    }

    for (i=1; i<=10; i++) {     
        pid=fork(); 
       if (pid == 0){       
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());       
            sleep(15); // child working ...       
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());        
            exit(0);     
        }
    }   
    for (i=1 ;i<=11; i++) {      
        printf("PARENT: working hard (task no. %d) ...\n",i);     
        n=20; while((n=sleep(n))!=0);     
        printf("PARENT: end of task no. %d\n",i);     
        printf("PARENT: waiting for child no. %d ...\n",i);
        if (pid != -1)       
            printf("PARENT: child with PID=%d terminated with exit code %d\n",pid,WEXITSTATUS(status));   
    }   
    exit(0); 
} 