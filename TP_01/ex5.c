#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[], char * envp[]){
    /* Alinea a & b
    int i;
    char *user;
    for (i = 0; envp[i] != NULL; i++){
        if(strncmp(envp[i], "USER=",5)==0){
            user=strtok(envp[i],"=");
            user=strtok(NULL,"=");
            printf("\nHello %s!\n", user);
        }
    }*/
    //printf("\nHello %s!\n", getenv("USER"));
    printf("\nHello %s!\n", getenv("USER_NAME"));
    return 0;
}