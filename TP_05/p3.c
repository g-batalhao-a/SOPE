#include<stdio.h> 
#include<stdlib.h> 
#define MAXLINE 1000 
#define PAGER "sort" 
int main(int argc, char *argv[]) { 
    char line[MAXLINE];   
    FILE *fpin, *fpout; 
    if (argc != 2) { 
        printf("usage: %s filename\n",argv[0]); 
        exit(1); 
    }   
    fpin = fopen(argv[1], "r");   
    fpout = popen(PAGER, "w"); 
    while (fgets(line, MAXLINE, fpin) != NULL)     
        fputs(line, fpout) == EOF;   
        
    pclose(fpout);   
    exit(0); 
}