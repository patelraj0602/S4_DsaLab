#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONG_MAX 1000000000
#define LONG_MIN -100000000

struct node{
    int val;
    struct node* left;
    struct node* right;
};

struct node* createNode(int val){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    now->val = val;
    now->left=NULL;
    now->right=NULL;
    return now;
}

struct node* make_tree(char* s, int low, int high){
    if(s[low+1]==')') return NULL;

    int num = 0;
    while(s[++low]!='(') num = (num*10)+(s[low]-'0');
    struct node* now = createNode(num);

    int mid = low+1;
    int tmp=1;
    while(tmp){
        if(s[mid]=='(') tmp++;
        else if(s[mid]==')') tmp--;
        mid++;
    }

    now->left = make_tree(s,low,mid-1);
    now->right = make_tree(s,mid,high-1);
    return now;
}

int isbst(struct node * root, long min, long max)
{
    if(!root) return 1;
    if(root->val <= min || root->val >= max) return 0;
    return isbst(root->left, min, root->val) && isbst(root->right, root->val, max);
}

int noNodes(struct node * root){
    if(root==NULL) return 0;
    return noNodes(root->left)+noNodes(root->right)+1;
}

int maximum(int a,int b){
    if(a>b) return a;
    return b;
}

void show_time(struct node* root){
    if(!root) return;
    printf("%d ",root->val);
    show_time(root->left);
    show_time(root->right);
}


void deleteMemory(struct node* root){
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
    char s[1000];
    char str[1000];

    scanf("%[^\n]s",str);
    int l = strlen(str);
    int i=-1;
    for(int j=0; j<l; j++){
        if(str[j]==' ') continue;
        s[++i]=str[j];
    }
    s[i]='\0';

    struct node* root = make_tree(s,0,i-1);

    struct node** now = (struct node**)malloc(1000*(sizeof(struct node*)));
    int low = -1;
    int high = -1;
    int ans = 0;

    now[++high]=root;
    while(low!=high){
        struct node* cur = now[++low];
        if(isbst(cur,LONG_MIN,LONG_MAX))
            ans=maximum(ans, noNodes(cur));
        else{
            if(cur->left) now[++high]=cur->left;
            if(cur->right) now[++high]=cur->right;
        }
    }

    printf("%d\n",ans);
    deleteMemory(root);
    free(now);
}