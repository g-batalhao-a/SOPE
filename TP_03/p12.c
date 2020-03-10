#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
int main(int argc, char *argv[]) { 
    int pid;  
    char *com[]={"cp","-n",argv[1],argv[2]}; 
    if (argc != 3) {   
        printf("Usage: %s <dirname> OR Usage: %s <dirname> <destinationfile>\n", argv[0], argv[0]); 
        exit(1);  
    }  
    printf("before fork\n");   
    pid=fork(); 
    if (pid > 0) {     
        wait(NULL);     
        printf("I'm the parent (PID=%d)\n\n",getpid()); 
    } 
    else {     
        printf("I'm the son (PID=%d)\n\n",getpid());     
        //system("ls /usr/include/s*.h -la"); //NOTE: system() "expands" s*.h     
        system(com);     
        printf("\n AFTER system() call\n"); 
        //WHY NOT FAILED, in this case, like in exec()     
        exit(0);   
    }   
    printf ("PID=%d exiting ...\n",getpid()); 
    return 0;
}