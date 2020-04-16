#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define MAX_NAME_LEN 50

struct cln_msg{
    char msg[MAX_NAME_LEN];
};

void * func(void * arg){
    int fd_dummy,num1,num2;
    struct cln_msg *cop;
    cop=(struct cln_msg *) arg;
    char fifo_name[MAX_NAME_LEN];
    void *r;
    r=malloc(sizeof(int));
    sscanf(cop->msg,"%d:%d:%s",&num1,&num2,fifo_name);
    *(int *)r=0;

    if(num1!=0 || num2!=0){
        printf("Operands: %d e %d. FIFO name = %s\n",num1,num2,fifo_name);
        fd_dummy=open(fifo_name,O_WRONLY);
        char client_msg[MAX_NAME_LEN];
        sprintf(client_msg,"Sum=%d\tSub=%d\tMult=%d\tDiv=%d\n",num1+num2,num1-num2,num1*num2,num1/num2);
        write(fd_dummy,&client_msg,MAX_NAME_LEN);
        close(fd_dummy);
        *(int *)r=1;
    }
    
    return r;
}

int main(void)
{
    int fd;//, fd_dummy;
    char msg[MAX_NAME_LEN];
    //char fifo_name[MAX_NAME_LEN];
    int num[2];
    struct cln_msg cm;
    pthread_t t;

    void *rt;

    if (mkfifo("./fifo_req",0660)<0)
        if (errno == EEXIST) printf("FIFO './fifo_req' already exists\n");
        else printf("Can't create FIFO\n");
    else 
        printf("FIFO './fifo_req' sucessfully created\n");
    
    if ((fd=open("./fifo_req",O_RDONLY)) !=-1)
        printf("FIFO './fifo_req' openned in READONLY mode\n");
    
    /*if ((fd_dummy=open("./fifo_req",O_WRONLY)) !=-1)
        printf("FIFO './fifo_req' openned in WRITEONLY mode\n");*/

    do{
        if(read(fd,&msg,MAX_NAME_LEN)){
            strcpy(cm.msg,msg);
            pthread_create(&t,NULL,func,(void *)&cm);
            pthread_join(t,&rt);
            /*
            sscanf(msg,"%d:%d:%s",&num[0],&num[1],fifo_name);
            if(num[0]!=0 || num[1]!=0){
                printf("Operands: %d e %d. FIFO name = %s\n",num[0],num[1],fifo_name);
                fd_dummy=open(fifo_name,O_WRONLY);
                char client_msg[MAX_NAME_LEN];
                sprintf(client_msg,"Sum=%d\tSub=%d\tDiv=%d\tDiv=%d\n",num[0]+num[1],num[0]-num[1],num[0]*num[1],num[0]/num[1]);
                write(fd_dummy,&client_msg,MAX_NAME_LEN);
                close(fd_dummy);
            }*/
        }
        
        //sleep(2);
    }while(*(int *)rt==1);
    free(rt);

    close(fd);


    if (unlink("./fifo_req")<0)
        printf("Error when destroying FIFO './fifo_req'\n");
    else
        printf("FIFO './fifo_req' has been destroyed\n");
    

    
    
    pthread_exit(0);
} 