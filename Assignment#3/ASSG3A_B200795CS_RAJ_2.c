#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct treeNode{
    int val;
    struct treeNode* p;
    struct treeNode* left;
    struct treeNode* right;
};

struct treeNode* createNode(int val){
    struct treeNode* now = (struct treeNode*)malloc(sizeof(struct treeNode));
    now->val=val;
    now->p=NULL;
    now->left=NULL;
    now->right=NULL;
    return now;
}

void insert(struct treeNode** root, int val){
    struct treeNode* now = createNode(val);
    struct treeNode* y = NULL;
    struct treeNode* x = *root;
    while(x!=NULL){
        y=x;
        if(now->val < x->val) x=x->left;
        else x=x->right;
    }
    now->p=y;
    if(y==NULL) *root=now;
    else if(now->val < y->val) y->left=now;
    else y->right=now;
}

int max(int a, int b){
    if(a>b) return a;
    return b;
}

int height(struct treeNode* root){
    if(!root) return 0;
    return max(height(root->left),height(root->right))+1;
}

int isAVL(struct treeNode* root){
    if(!root) return 1;
    
    int val = height(root->left)-height(root->right);
    if(abs(val)<=1) val=1;
    else val=0;

    return (val && isAVL(root->left) && isAVL(root->right));
}

void deleteMemory(struct treeNode* root){
    if(root==NULL) return;
    deleteMemory(root->left);
    deleteMemory(root->right);
    free(root);
}

int main(){
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    struct treeNode* root = NULL;
    while(1){
        char c; scanf(" %c",&c);
        if(c=='i'){
            int val; scanf("%d",&val);
            insert(&root,val);
        }
        else if(c=='c')
            printf("%d\n", isAVL(root));

        else{
            deleteMemory(root);
            return 0;
        }
    }
}
 