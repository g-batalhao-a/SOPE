#include <stdio.h>
#include <stdlib.h>

void function_1(){
    printf("Executing exit handler 1\n");
    //exit(0);
}
void function_2(){
    printf("Executing exit handler 2\n");
    exit(0);
}

int main(){
    int value_1,value_2;
    value_1=atexit(function_1);value_2=atexit(function_2);
    if(value_1!=0 || value_2!=0){
        printf("Error in exiting auxiliary functions!\n");
    }
    //abort();
    printf("Main done!\n");
    exit(0);  // zero é geralmente indicativo de "sucesso" 
} 