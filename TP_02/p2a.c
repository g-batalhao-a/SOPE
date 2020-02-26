#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> 
#include <errno.h> 
#include <string.h>
#define BUFFER_SIZE 512 
#define SIZE 1
#define NUMELEM 6

int main(int argc, char *argv[]) { 
    FILE* fd1=NULL;FILE* fd2=NULL;
    int nr, nw;
    char buffer[BUFFER_SIZE];

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }
    fd1 = fopen(argv[1], "r");
        if (fd1 == NULL) {
        perror(argv[1]);
        return 2;
    }
    fd2 = fopen(argv[2], "w");
    if (fd2 == NULL) {
        perror(argv[2]);
        fclose(fd1);
        return 3;
    }

    nr = fread(buffer, SIZE, NUMELEM,fd1);
    if (nr!=SIZE*NUMELEM) {
        perror(argv[1]);
        fclose(fd1);
        fclose(fd2);
        return 4;
    }
    nw = fwrite(buffer, SIZE, strlen(buffer),fd2);
    if(nw!=SIZE*NUMELEM || nw != nr){
        perror(argv[2]);
        fclose(fd1);
        fclose(fd2);
        return 5;
    }
    fclose(fd1);
    fclose(fd2);
    return 0;
} 
