#include <stdio.h>
#include <stdlib.h>

struct queue{
    int tail,head;
    int* arr;
};

int isFull(struct queue* q, int n){
    if(q->tail >= n-1) return 1;
    return -1;
}

void enqueue(struct queue* q, int n, int val){
    if(isFull(q,n)==1) printf("1\n");
    else{
        q->tail++;
        q->arr[q->tail]=val;
    }
}

int isEmpty(struct queue* q){
    if(q->head == q->tail) return 1;
    return -1;
}

void dequeue(struct queue* q){
    if(isEmpty(q)==1) printf("1\n");
    else{
        q->head++;
        printf("%d\n",q->arr[q->head]);
    }
}

int main(){
    int n; scanf("%d",&n);
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    int* a = (int*)malloc(n*sizeof(int));
    q->arr = a;
    q->head=-1;
    q->tail=-1;

    char c;
    while(1){
        scanf(" %c",&c);
        if(c=='i'){
            int val; scanf("%d",&val);
            enqueue(q,n,val);
        }
        else if(c=='d') dequeue(q);

        else if(c=='e') printf("%d\n",isEmpty(q));

        else if(c=='f') printf("%d\n",isFull(q,n));

        else{
            free(q->arr);
            free(q);
            return 0;
        }
    }
}