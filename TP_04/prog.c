#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h>
#include <time.h>

int main(int argc, char* argv[]){  
    int time=0;
    while(time!=30){
        printf("%s\n",argv[1]);
        time+=5;
        sleep(5);
    }
        
    return 0;
} 