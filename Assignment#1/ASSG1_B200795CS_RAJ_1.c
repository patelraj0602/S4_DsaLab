#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    struct node* left;
    struct node*right;
    struct node* parent;
};


//Queue to store the info of treenode
struct queue{
    int tail,head;
    struct node** arr;
};

int isFull(struct queue* q, int n){
    if(q->tail >= n-1) return 1;
    return 0;
}

void push(struct queue* q, int n, struct node* val){
    if(isFull(q,n)) printf("The queue is full\n");
    else{
        q->tail++;
        q->arr[q->tail]=val;
    }
}

int isEmpty(struct queue* q){
    if(q->head == q->tail) return 1;
    return 0;
}

void pop(struct queue* q){
    if(isEmpty(q)) printf("The queue is Empty\n");
    else q->head++;
}

struct node* front(struct queue* q){
    return q->arr[q->head+1];
}




// Working with binary tree from here
struct node* createNode(int val){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    now->key = val;
    now->left = NULL;
    now->right = NULL;
    now->parent = NULL;
    return now;
}

void make_tree(struct queue* q, int n, struct node* now, struct node** root){
    push(q,n,now);
    if(*root == NULL) *root = now;
    else{
        struct node* top = front(q);
        now->parent = top;
        if(top->left==NULL) top->left=now;
        else{
            top->right=now;
            pop(q);
        }
    }
}

void show_time(struct node* root){
    printf("(");
    if(!root){
        printf(")");
        return;
    } 
    printf("%d",root->key);

    show_time(root->left);
    show_time(root->right);

    printf(")");
}

int main(){
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    int n=1000;
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    struct node** a = (struct node**)malloc(n*sizeof(struct node*));
    q->arr = a; q->head=-1; q->tail=-1;

    struct node* root = NULL;
    while(1){
        char c; scanf(" %c",&c);

        if(c=='i'){
            int val; scanf("%d",&val);
            struct node* now = createNode(val);
            make_tree(q,n,now,&root);
        }
        else if(c=='p'){
            show_time(root);
        }
        else{
            for(int i=0; i<=q->tail; i++) free(q->arr[i]);
            free(a);
            free(q);
            return 0;
        }
    }
}