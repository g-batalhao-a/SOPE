// PROGRAMA p1.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int global=1;
int main(void) {   
    int local = 2;   
    if(fork() > 0) { //Parent    
        printf("PID = %d; PPID = %d\n", getpid(), getppid());     
        global++;     
        local--;   
    } 
    else {     //child
        printf("PID = %d; PPID = %d\n", getpid(), getppid());     
        global--;     
        local++;   
    }   
    printf("PID = %d - global = %d ; local = %d\n", getpid(), global, local);   
    return 0; 
} 