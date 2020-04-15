#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

#define MAX_MSG_LEN 50

int main(int argc, char *argv[])
{
    int fd, fd_dummy;
    int num[2];
    char fifoName[MAX_MSG_LEN];

    if (argc!=3) {
        printf("Usage: p6client <num1> <num2>\n");
        exit(1);
    }

    fd=open("./fifo_req",O_WRONLY);

    if (fd == -1) {
        printf("Oops !!! Service is closed !!!\n");
        exit(1);
    }

    printf("FIFO 'requests' openned in WRITEONLY mode\n");

    char msg[MAX_MSG_LEN];
    sprintf(fifoName, "fifo_ans_%d",getpid());
    sprintf(msg,"%d:%d:%s",atoi(argv[1]),atoi(argv[2]),fifoName);

    write(fd,&msg,MAX_MSG_LEN);

    close(fd);
    if(atoi(argv[1])!=0 || atoi(argv[2])!=0){
        if (mkfifo(fifoName,0660)<0)
            if (errno == EEXIST) printf("FIFO '%s' already exists\n",fifoName);
            else printf("Can't create FIFO\n");
        else 
            printf("FIFO '%s' sucessfully created\n",fifoName);
        
        if ((fd_dummy=open(fifoName,O_RDONLY)) !=-1)
            printf("FIFO '%s' openned in READONLY mode\n",fifoName);

        char server_msg[MAX_MSG_LEN];

        read(fd_dummy,&server_msg,MAX_MSG_LEN);
        printf("%s",server_msg);
        close(fd_dummy);
    }

    return 0;
} 