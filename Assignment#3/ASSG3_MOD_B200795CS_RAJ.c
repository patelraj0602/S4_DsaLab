#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int val;
    struct node* left;
    struct node* right;
    struct node* p;
    int color;                                                          // (red-color=0 AND black-color=1)
};

struct node* createNode(int val){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    now->val=val;
    now->left=NULL;
    now->right=NULL;
    now->p=NULL;
    now->color=0;
}

struct node* LeftRotate(struct node* now){

    struct node *y = now->right;
    struct node *T2 = y->left;
    y->left = now;
    now->right = T2;

    struct node* temp = now->p;
    y->p=temp;
    now->p=y;
    if(temp){
        if(temp->left==now) temp->left=y;
        else temp->right=y;
    }
    return y;
}

struct node* RightRotate(struct node* now){

    struct node *x = now->left;
    struct node *T2 = x->right;
    x->right = now;
    now->left = T2;

    struct node* temp = now->p;
    x->p=temp;
    now->p=x;
    if(temp){
        if(temp->left==now) temp->left=x;
        else temp->right=x;
    }
    return x;
}

void fixTree(struct node** root, struct node* now){
    while((now) && (now->p) && (now->p->p) && ((!now->p->color)&&(!now->color))){
        struct node* uncle;
        if(now->p == now->p->p->left) uncle=now->p->p->right;
        else uncle=now->p->p->left;

        if((uncle)&&(!uncle->color)){
            uncle->color=1;
            now->p->color=1;
            now->p->p->color=0;
            now=now->p->p;
        }
        else{
            struct node* parent = now->p;
            struct node* gp = parent->p;
            if((parent->left==now) && (gp->left==parent))
                now = RightRotate(gp);
            
            else if((parent->right==now) && (gp->right==parent))
                now = LeftRotate(gp);

            else if((parent->right==now) && (gp->left==parent)){
                now = LeftRotate(parent);
                now = RightRotate(gp);
            }
            else{
                now = RightRotate(parent);
                now = LeftRotate(gp);
            }
            now->color=1;
            if(now->left) now->left->color=0;
            if(now->right) now->right->color=0;

            // If we rotated the root node then change the pointer inside root.
            if(*root==gp) *root=now;
        }
    }
    (*root)->color=1;
}

void insert(struct node** root, int val){
    struct node* now = createNode(val);
    struct node* y = NULL;
    struct node* x = *root;
    while(x){
        y=x;
        if(now->val < x->val) x=x->left;
        else x=x->right;
    }
    now->p=y;
    if(y==NULL) *root=now;
    else if(now->val < y->val) y->left=now;
    else y->right=now;

    fixTree(root,now);
}

int CheckBeautiful(struct node* root){
    int front=-1;
    int back=-1;
    struct node* arr[2000];

    arr[++front]=root;
    int c=1;
    while(front!=back){
        int len = front-back;
        for(int i=0; i<len; i++){
            struct node* now = arr[++back];
            if(now->color!=c) return -1;
            else{
                if(now->left) arr[++front]=now->left;
                if(now->right) arr[++front]=now->right;
            }
        }
        c=(c)?0:1;
    }
    return 1;
}



void showTime(struct node* root){
    printf("( ");
    if(root != NULL){
        if(root->color==1) printf("%d B ", root->val);
        else printf("%d R ", root->val);
        showTime(root->left);
        showTime(root->right);
    }
    printf(") ");
}

void deleteMemory(struct node* root){
    if(root==NULL) return;
    deleteMemory(root->left);
    deleteMemory(root->right);
    free(root);
}

int main(){
    #ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	struct node* root=NULL;
	int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int key; scanf("%d",&key);
        insert(&root,key);
    }
    int val=CheckBeautiful(root);
    printf("%d\n",val);
    
    deleteMemory(root);
}