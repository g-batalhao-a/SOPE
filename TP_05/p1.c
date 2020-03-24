
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAXLINE 10
#define READ 0
#define WRITE 1

struct Numbers{
    int num1;
    int num2;
};

int main(){
    struct Numbers number;
    int n, fd[2];
    pid_t pid;

    if(pipe(fd)<0){
        fprintf(stderr,"Pipe Error");
        exit(1);
    }

    if((pid=fork())<0){
        fprintf(stderr,"Fork Error");
        exit(2);
    }
    else if(pid>0){
        int num[2];
        char str1[2][MAXLINE];
        printf("PARENT:\n");
        printf("x y ? "); 
        //scanf("%d %d",&num[0],&num[1]);
        //scanf("%d %d",&number.num1,&number.num2);
        scanf("%s %s",str1[0],str1[1]);
        close(fd[READ]);
        write(fd[WRITE],str1,2*sizeof(char*));
        close(fd[WRITE]);
    }
    else{
        struct Numbers number2;
        int numb[2];
        char str2[2][MAXLINE];
        close(fd[WRITE]);
        read(fd[READ],str2,2*sizeof(char*));
        printf("SON:\n");
        /*
        printf("x+y= %d\n", numb[0]+numb[1]);
        printf("x-y= %d\n", numb[0]-numb[1]);
        printf("x*y= %d\n", numb[0]*numb[1]);
        if(numb[1]!=0)
            printf("x/y= %d\n", numb[0]/numb[1]);
        else
            printf("Invalid Operation (dividend is 0)");
        */
        /*
        printf("x+y= %d\n", number2.num1+number2.num2);
        printf("x-y= %d\n", number2.num1-number2.num2);
        printf("x*y= %d\n", number2.num1*number2.num2);
        if(number2.num2!=0)
            printf("x/y= %d\n", number2.num1/number2.num2);
        else
            printf("Invalid Operation (dividend is 0)");
        */

        printf("x+y= %d\n", atoi(str2[0])+atoi(str2[1]));
        printf("x-y= %d\n", atoi(str2[0])-atoi(str2[1]));
        printf("x*y= %d\n", atoi(str2[0])*atoi(str2[1]));
        if(atoi(str2[1])!=0)
            printf("x/y= %f\n", atof(str2[0])/atof(str2[1]));
        else
            printf("Invalid Operation (dividend is 0)");
        close(fd[READ]);
        
    }
    exit(0);
}