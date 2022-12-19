#include <stdio.h>
#include <stdlib.h>

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

void insert(struct treeNode** root, struct treeNode* now){
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

struct treeNode* search(struct treeNode* root, int val){
    if((root==NULL)||(root->val == val)) return root;

    if(val < root->val) return search(root->left,val);
    else return search(root->right, val);
}

struct treeNode* treeMin(struct treeNode* root){
    while(root->left) root=root->left;
    return root;
}

struct treeNode* treeMax(struct treeNode* root){
    while(root->right) root=root->right;
    return root;
}

// Refer the predecessor and successor algorithms for the tress which does not have parent.
struct treeNode* predecessor(struct treeNode* root, int val){
    struct treeNode* now = search(root,val);

    if(now->left) return treeMax(now->left);
    struct treeNode* y = now->p;
    while((y)&&(now==y->left)){
        now=y;
        y=y->p;
    }
    return y;
}

struct treeNode* successor(struct treeNode* root, int val){
    struct treeNode* now = search(root,val);

    if(now->right) return treeMin(now->right);
    struct treeNode* y = now->p;
    while((y)&&(now==y->right)){
        now=y;
        y=y->p;
    }
    return y;
}

void transplant(struct treeNode** root, struct treeNode* u, struct treeNode* v){
    if(u->p == NULL) *root=v;
    else if(u==u->p->left) u->p->left=v;
    else u->p->right=v;

    if(v!=NULL) v->p=u->p;
}

int deleteNode(struct treeNode** root, int val){
    struct treeNode* now = search(*root,val);
    if(now==NULL) return -1;

    if(now->left == NULL) transplant(root,now,now->right);
    else if(now->right == NULL) transplant(root,now,now->left);
    else{
        struct treeNode* y=treeMin(now->right);
        if(y->p != now){
            transplant(root,y,y->right);
            y->right=now->right;
            y->right->p=y;
        }
        transplant(root,now,y);
        y->left=now->left;
        y->left->p=y;
    }
    int bk = now->val;
    free(now);
    return bk;
}

int level(struct treeNode* root, int k){
    if(!search(root,k)) return -1;

    int lvl = 1;
    while(root->val!=k){
        if(root->val>k) root=root->left;
        else root=root->right;
        lvl++;
    }
    return lvl;
}

void inorder(struct treeNode* root){
    if(root == NULL) return;

    inorder(root->left);
    printf("%d ",root->val);
    inorder(root->right);
}

void postorder(struct treeNode* root){
    if(root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ",root->val);
}

void preorder(struct treeNode* root){
    if(root == NULL) return;

    printf("%d ",root->val);
    preorder(root->left);
    preorder(root->right);
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

        if(c=='a'){
            int v; scanf("%d",&v);
            struct treeNode* now = createNode(v);
            insert(&root,now);
        }
        
        else if(c=='d'){
            int val; scanf("%d",&val);
            int dn = deleteNode(&root,val);
            printf("%d\n",dn);
        }

        else if(c=='s'){
            int val; scanf("%d",&val);
            struct treeNode* now = search(root,val);
            if(now!=NULL) printf("1\n");
            else printf("-1\n");
        }

        else if(c=='l'){
            int val; scanf("%d",&val);
            printf("%d\n",level(root,val));
        }

        else if(c=='m'){
            struct treeNode* now = treeMin(root);
            printf("%d\n",now->val);
        }

        else if(c=='x'){
            struct treeNode* now = treeMax(root);
            printf("%d\n",now->val);
        }

        else if(c=='r'){
            int val; scanf("%d",&val);
            if(search(root,val)){
                struct treeNode* pre = predecessor(root,val);
                if(pre) printf("%d\n",pre->val);
                else printf("-1\n");
            }
            else printf("-1\n");
        }

        else if(c=='u'){
            int val; scanf("%d",&val);
            if(search(root,val)){
                struct treeNode* suc = successor(root,val);
                if(suc) printf("%d\n",suc->val);
                else printf("-1\n");
            }
            else printf("-1\n");
        }

        else if(c=='i'){
            inorder(root);
            printf("\n");
        }
        else if(c=='p'){
            preorder(root);
            printf("\n");
        }
        else if(c=='t'){
            postorder(root);
            printf("\n");
        }
        else{
            deleteMemory(root);
            return 0;
        }
    }
}
