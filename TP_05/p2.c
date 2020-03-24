#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAXLINE 10
#define READ 0
#define WRITE 1
int main(){
    int n, fd[2], fd1[2];
    pid_t pid;

    if(pipe(fd)<0 ||pipe(fd1)){
        fprintf(stderr,"Pipe Error");
        exit(1);
    }

    if((pid=fork())<0){
        fprintf(stderr,"Fork Error");
        exit(2);
    }
    else if(pid>0){
        int num[2];
        int op2[4];
        printf("PARENT:\n");
        printf("x y ? "); 
        scanf("%d %d",&num[0],&num[1]);
        close(fd[READ]);
        write(fd[WRITE],num,2*sizeof(int));
        close(fd[WRITE]);
        read(fd1[READ],op2,4*sizeof(int));
        printf("x+y= %d\n", op2[0]);
        printf("x-y= %d\n", op2[1]);
        printf("x*y= %d\n", op2[2]);
        printf("x/y= %d\n", op2[3]);
    }
    else{
        int numb[2];
        int op[4];
        close(fd[WRITE]);
        read(fd[READ],numb,2*sizeof(int));
        printf("SON:\n");
        
        op[0]= numb[0]+numb[1];
        op[1]= numb[0]-numb[1];
        op[2]= numb[0]*numb[1];
        if(numb[1]!=0)
            op[3]=numb[0]/numb[1];
        else
            op[3]=0;
       
        close(fd[READ]);
        write(fd1[WRITE],op,4*sizeof(int));
        close(fd1[WRITE]);
        
    }
    exit(0);
}