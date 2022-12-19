#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode{
    char firstName[100],lastName[100];
    int age;
    struct treeNode* p;
    struct treeNode* left;
    struct treeNode* right;
};

struct treeNode* arr[128];

struct treeNode* createNode(char* firstName, char* lastName, int age){
    struct treeNode* now = (struct treeNode*)malloc(sizeof(struct treeNode));
    strcpy(now->firstName, firstName);
    strcpy(now->lastName, lastName);
    now->age = age;
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
        if(now->age < x->age) x=x->left;
        else x=x->right;
    }
    now->p=y;
    if(y==NULL) *root=now;
    else if(now->age < y->age) y->left=now;
    else y->right=now;
}

void insertData(char* firstName, char* lastName, int age){
    int val = 0;
    int len = strlen(lastName);
    for(int i=0; i<len; i++) val+=(int)lastName[i];
    val=val%128;

    struct treeNode* now = createNode(firstName,lastName,age);
    insert(&arr[val],now);
}

int isPresent(struct treeNode* root, char* firstName, char* lastName){
    if(root==NULL) return 0;
    if((strcmp(root->firstName,firstName)==0)&&(strcmp(root->lastName,lastName)==0)) return 1;
    return (isPresent(root->left,firstName,lastName)|isPresent(root->right,firstName,lastName));
}

void printRelatives(char* firstName, char* lastName){
    int val = 0;
    int len = strlen(lastName);
    for(int i=0; i<len; i++) val+=(int)lastName[i];
    val=val%128;

    struct treeNode* root = arr[val];
    
    if(!isPresent(root,firstName,lastName)){
        printf("-1\n");
        return;
    }

    while(root){
        printf("%s %s %d\n",root->firstName,root->lastName,root->age);

        if(isPresent(root->left,firstName,lastName)) root=root->left;
        else if(isPresent(root->right,firstName,lastName)) root=root->right;
        else return;
    }
}

void deleteMemory(struct treeNode* root){
    if(root==NULL) return;
    deleteMemory(root->left);
    deleteMemory(root->right);
    free(root);
}


void cleaner(){
    for(int i=0; i<128; i++)
        deleteMemory(arr[i]);
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    for(int i=0; i<128; i++) arr[i]=NULL;

    while(1){
        char c; scanf(" %c",&c);
        if(c=='i'){
            char firstName[100],lastName[100];
            int age;
            scanf("%s %s %d",firstName,lastName,&age);
            insertData(firstName,lastName,age);
        }
        else if(c=='p'){
            char firstName[100],lastName[100];
            scanf("%s %s",firstName,lastName);
            printRelatives(firstName,lastName);

        }
        else{
            cleaner();
            return 0;
        }
    }
}
