// PROGRAMA p8.c 
#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[], char *envp[]) {    
    pid_t pid;
    int pfd;
    char *com[] = {"ls", "-laR", NULL};
    if ((argc != 3) && (argc!=2)) {   
        printf("Usage: %s <dirname> OR Usage: %s <dirname> <destinationfile>\n", argv[0], argv[0]); 
        exit(1);  
    }  
    pid=fork();    
    if (pid > 0)      
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);    
    else if (pid == 0){     
        if(argc==3){
            pfd=open(argv[2],O_WRONLY|O_CREAT,0666);
            close(1);
            dup(pfd);
        }
        execlp("ls","ls","-laR",argv[1],NULL);      
        //execl("/bin/ls","ls","-laR",argv[1],NULL);
        //execvp("ls",com);    
        //execv("/bin/ls",com);
        //execve("/bin/ls",com,envp);
        printf("Command not executed !\n");      
        exit(1);    
    }    
    exit(0); 
}