#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    int degree;
    struct node* sibling;
    struct node* child;
    struct node* parent;
};

struct node* make_heap(){
    struct node* now = NULL;
    return now;
}

struct node* createNode(int k){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    now->val = k;
    now->degree = 0;
    now->sibling = NULL;
    now->child = NULL;
    now->parent = NULL;
    return now;
}

void binomialLink(struct node* y, struct node* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree+1;
}

struct node* BinomialHeapMerge(struct node* h1, struct node* h2){
    if(!h1) return h2;
    if(!h2) return h1;

    struct node* ret = NULL;
    struct node* root = NULL;
    while(h1 && h2){
        if((h1->degree)<(h2->degree)){
            if(!root) {
                ret=h1;
                root=h1;
            }
            else{
                root->sibling=h1;
                root=root->sibling;
            }
            h1=h1->sibling;
        }
        else{
            if(!root){
                ret=h2; 
                root=h2;
            }
            else{
                root->sibling=h2;
                root=root->sibling;
            }
            h2=h2->sibling;
        }
    }
    if(h1) root->sibling=h1;
    else root->sibling=h2;

    return ret;
}

void printer(struct node* root){
    struct node* arr[1000];
    int l=-1; int h=-1;

    arr[++h]=root;
    while(l!=h){
        int len=h-l;
        for(int i=0; i<len; i++){
            struct node* top = arr[++l];
            while(top){
                printf("%d ",top->val);
                if(top->child) arr[++h]=top->child;
                top=top->sibling;
            }
        }
    }
    printf("\n");
}

struct node* BinomialHeapUnion(struct node* h1, struct node* h2){
    struct node* h = BinomialHeapMerge(h1,h2);

    if(!h) return h;
    struct node* pre = NULL;
    struct node* x = h;
    struct node* next = x->sibling;
    while(next){
        if((x->degree!=next->degree)||((next->sibling)&&(next->sibling->degree==x->degree))){ 
            pre = x;
            x = next;
        }
        else if(x->val <= next->val){
            x->sibling = next->sibling;
            binomialLink(next,x);
        }
        else{
            if(!pre) h=next;
            else pre->sibling = next;
            binomialLink(x,next);
            x = next;
        }
        next = x->sibling;
    }
    return h;
}

int Minimum(struct node* root){
    int min = 10000000;
    while(root){
        if(root->val < min)
            min = root->val;
        root=root->sibling;
    }
    if(min==10000000) min=-1;
    return min;
}

struct node* Insert(struct node* root, int k){
    struct node* h1 = createNode(k);
    root = BinomialHeapUnion(root,h1); 
    return root;
}

struct node* reverseList(struct node* head) {
    struct node* nextNode;
    struct node* prevNode=0;
    while(head){
        nextNode=head->sibling;
        head->sibling=prevNode;
        prevNode=head;
        head=nextNode;
    }
    return prevNode;
}

struct node* ExtractMin(struct node* root){
    struct node* first = root;
    struct node* second = NULL;
    int min = Minimum(root);
    struct node* pre = NULL;
    while(root->val!=min){
        pre=root;
        root=root->sibling;
    }
    if(!pre) first=root->sibling;
    else pre->sibling=root->sibling;
    second = reverseList(root->child);

    free(root);
    return BinomialHeapUnion(first,second);
}

struct node* findNode(struct node* root, int required){
    struct node* arr[1000];
    int l=-1; int h=-1;

    arr[++h]=root;
    while(l!=h){
        int len=h-l;
        for(int i=0; i<len; i++){
            struct node* top = arr[++l];
            while(top){
                if(top->val == required) return top;
                if(top->child) arr[++h]=top->child;
                top=top->sibling;
            }
        }
    }
    return NULL;
}

void swap(struct node* first, struct node* second){
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
}

struct node* DecreaseKey(struct node* root, int x, int k){
    struct node* cnode = findNode(root,x);
    if(!cnode) return NULL;

    cnode->val-=k;
    while((cnode->parent)&&(cnode->val < cnode->parent->val)){
        swap(cnode,cnode->parent);
        cnode = cnode->parent;
    }
    return cnode;
}

struct node* deleteNode(struct node* root, int x){
    int k = 100000000;
    struct node* dnode = DecreaseKey(root,x,k);
    if(dnode) {
        printf("%d\n",x);
        return ExtractMin(root);
    }
    else{
        printf("-1\n");
        return root;
    }
}

void deleteMemory(struct node* root){
    struct node* arr[1000];
    int l=-1; int h=-1;

    arr[++h]=root;
    while(l!=h){
        int len=h-l;
        for(int i=0; i<len; i++){
            struct node* top = arr[++l];
            while(top){
                struct node* del = top;
                if(top->child) arr[++h]=top->child;
                top=top->sibling;
                free(del);
            }
        }
    }
}

int main(){

    struct node* root = NULL;
    while(1){
        char c; scanf(" %c",&c);
        if(c=='i'){
            int k; scanf("%d",&k);
            root = Insert(root,k);
        }
        else if(c=='p') printer(root);
        else if(c=='m') printf("%d\n",Minimum(root));
        else if(c=='x') {
            int val = Minimum(root);
            printf("%d\n",val);
            if(val>0) root=ExtractMin(root);
        }
        else if(c=='r'){
            int y,z; scanf("%d %d",&y,&z);
            struct node* cnode = DecreaseKey(root,y,z);
            if(cnode) printf("%d\n",cnode->val);
            else printf("-1\n");
        }
        else if(c=='d'){
            int k; scanf("%d",&k);
            root = deleteNode(root, k);
        }
        else{
            deleteMemory(root);
            return 0;
        }
    }
}
