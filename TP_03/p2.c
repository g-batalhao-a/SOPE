// PROGRAMA p2.c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(void) {  
    //write(STDOUT_FILENO,"1",1);  
    printf("%d\n",1);
    if(fork() > 0) {    
        //write(STDOUT_FILENO,"2",1);    
        //write(STDOUT_FILENO,"3",1);  
        printf("%d",2);
        printf("%d",3);
    } 
    else {    
        //write(STDOUT_FILENO,"4",1);    
        //write(STDOUT_FILENO,"5",1);  
        printf("%d",4);
        printf("%d",5);

    }  
    //write(STDOUT_FILENO,"\n",1);  
    printf("\n");
    return 0; 
} 