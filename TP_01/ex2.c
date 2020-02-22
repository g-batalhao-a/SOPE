#include <stdio.h>
const int MAX_LEN = 50;
int main(void){   
    char str[MAX_LEN];
    fgets(str,MAX_LEN,stdin);

    int num;
    scanf("%d",&num);
    for(int x=0;x<num;x++){
        printf("Hello %s!\n",str);
    }
    return 0;
} 