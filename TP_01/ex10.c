#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
int main(int argc, char *argv[]){
    char buf[MAX];
    char *tokens[atoi(argv[1])]; //o argumento define o numero de tokens
    fgets(buf,MAX,stdin);
    char *token = strtok(buf," |;\n");
    int i=0;
    while(token!=NULL){
        tokens[i++]=token;
        token=strtok(NULL," |;\n");
    }
    for(i=0;i<atoi(argv[1]);i++){
        printf("Iteration %d: %s\n",i,tokens[i]);
    }
    return 0;
}