// PROGRAMA p05.c 
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h> 

#define NUM_THREADS 4

struct operand{
    int op1;
    int op2;
};

void * opsum(void * arg) {  
    struct operand *my_ops;
    my_ops=(struct operand *) arg;
    void *r;
    r=malloc(sizeof(int));
    //printf("%d+%d=%d\n",my_ops->op1,my_ops->op2,my_ops->op1+my_ops->op2);
    *(int *)r=my_ops->op1+my_ops->op2;
    return r; 
} 

void * opmin(void * arg) {  
    struct operand *my_ops;
    my_ops=(struct operand *) arg;
    void *r;
    r=malloc(sizeof(int));
    //printf("%d-%d=%d\n",my_ops->op1,my_ops->op2,my_ops->op1-my_ops->op2);
    *(int *)r=my_ops->op1-my_ops->op2;
    return r; 
} 

void * opmult(void * arg) {  
    struct operand *my_ops;
    my_ops=(struct operand *) arg;
    void *r;
    r=malloc(sizeof(int));
    //printf("%d*%d=%d\n",my_ops->op1,my_ops->op2,my_ops->op1*my_ops->op2);
    *(int *)r=my_ops->op1*my_ops->op2;
    return r; 
} 

void * opdiv(void * arg) {  
    struct operand *my_ops;
    my_ops=(struct operand *) arg;
    void *r;
    r=malloc(sizeof(int));
    //printf("%d/%d=%d\n",my_ops->op1,my_ops->op2,my_ops->op1/my_ops->op2);
    *(int *)r=my_ops->op1/my_ops->op2;
    return r; 
} 

int main() {    
    pthread_t ta, tb,tc,td; 
    void *ra,*rb, *rc, *rd;

    struct operand opps;
    printf("First operand: ");
    scanf("%d",&opps.op1);
    printf("\nSecond operand: ");
    scanf("%d",&opps.op2);

    pthread_create(&ta, NULL, opsum, (void *) &opps);   
    pthread_create(&tb, NULL, opmin, (void *) &opps);   
    pthread_create(&tc, NULL, opmult, (void *) &opps);   
    pthread_create(&td, NULL, opdiv, (void *) &opps); 

    pthread_join(ta, &ra);   
    pthread_join(tb, &rb);   
    pthread_join(tc, &rc);   
    pthread_join(td, &rd);   

    printf("\n%d+%d=%d\n",opps.op1,opps.op2,*(int *)ra);
    printf("\n%d-%d=%d\n",opps.op1,opps.op2,*(int *)rb);
    printf("\n%d*%d=%d\n",opps.op1,opps.op2,*(int *)rc);
    printf("\n%d/%d=%d\n",opps.op1,opps.op2,*(int *)rd);

    pthread_exit(0); 
} 