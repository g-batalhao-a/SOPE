// PROGRAMA p4a.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {  
    pid_t pid;
    int p;
    pid=fork();
    if(pid == 0) {    
        write(STDOUT_FILENO,"Hello ",6);
    } 
    else if(pid > 0){    
        wait(&p);
        write(STDOUT_FILENO,"world!\n",7);

    } 
    //printf("\n");
    return 0; 
} 