// PROGRAMA p5b.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
  int fd;
  char *text1="CCCCC";
  char *text2="DDDDD";

  fd = open("f1.txt", O_WRONLY|O_SYNC|O_APPEND,0600);
  if(fd==-1){
    perror("Error opening file!");
    return 1;
  }
  if(write(fd,text1,5)!=5 || write(fd,text2,5)!=5){
    perror("Error writing to file!");
    return 2;
  }
  close(fd);
  return 0;
}

