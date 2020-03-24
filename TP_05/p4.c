#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAXLINE 10
#define READ 0
#define WRITE 1
int main(int argc, char *argv[]){
    int n, fd[2], fd1[2];
    pid_t pid, pid2;

    if(pipe(fd)<0 ||pipe(fd1)){
        fprintf(stderr,"Pipe Error");
        exit(1);
    }

    if((pid=fork())<0){
        fprintf(stderr,"Fork Error");
        exit(2);
    }
    else if(pid>0){
        if((pid2=fork())<0){
            fprintf(stderr, "Fork Error");
            exit(3);
        }
        else if(pid>0){
            close(fd1[WRITE]);
            dup(fd1[WRITE]);
            execlp("ls","ls",argv[1],"-laR",NULL);
        }
        else{
            close(fd[WRITE]);
            dup(fd[WRITE]);
            close(fd[READ]);
            dup(fd1[READ]);
            execlp("grep","grep",argv[2],NULL);
        }
       
    }
    else{
        close(fd[READ]);
        dup(fd[READ]);
        execlp("sort","sort",NULL);
        
    }
    exit(0);
}