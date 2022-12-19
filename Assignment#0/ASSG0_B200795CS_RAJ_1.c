#include <stdio.h>
#include <stdlib.h>

struct stack{
    int top;
    int* arr;
};

int isFull(struct stack* sk, int n){
    if(sk->top >= n-1) return 1;
    return 0;
}

void push(struct stack* sk, int* n, int val){
    if(isFull(sk,*n)){
        printf("1\n");
        (*n)*=2;
        // int* tmp = sk->arr; 
        sk->arr = (int*)realloc(sk->arr, sizeof(int)*(2*(*n)));
        // free(tmp);  Memory loss occurs
    }
    sk->top++;
    sk->arr[sk->top] = val;
}

int isEmpty(struct stack* sk){
    if(sk->top<0) return 1;
    return 0; 
}

void pop(struct stack* sk){
    if(isEmpty(sk)) printf("-1\n");
    else{
        printf("%d\n",sk->arr[sk->top]);
        sk->top--;
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
    #endif
    int n; scanf("%d",&n);
    struct stack* sk = (struct stack*)malloc(sizeof(struct stack));
    int* a = (int*)malloc(n*sizeof(int));
    sk->top=-1;
    sk->arr=a;

    char c;
    while(1){
        scanf(" %c",&c);
        if(c=='i'){
            int i; scanf("%d",&i);
            push(sk,&n,i);
        }
        else if(c=='d'){
            pop(sk);
        }
        else{
            free(sk->arr);
            free(sk);
            return 0;
        }
    }
}

