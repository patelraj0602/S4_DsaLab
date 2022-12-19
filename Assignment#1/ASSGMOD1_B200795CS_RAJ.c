#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int val;
    struct node* left;
    struct node* right;
    struct node* parent;
};


struct node* createNode(int val){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    now->val = val;
    now->left=NULL;
    now->right=NULL;
    now->parent = NULL;
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

void addParent(struct node* root){
    if(root->left) {
        root->left->parent = root;
        addParent(root->left);
    }
    if(root->right){
        root->right->parent = root;
        addParent(root->right);
    }
}


struct node* level(struct node* root, int val){
    struct node** arr = (struct node**)malloc(1000*sizeof(struct node*));
    int low=-1; int high=-1;

    int lvl=1;
    arr[++high]=root;
    while(low!=high){
        int len=high-low;
        for(int i=0; i<len; i++){
            struct node* tmp = arr[++low];
            if(tmp->val == val){
                free(arr);
                return tmp;
            }
            else{
                if(tmp->left) arr[++high]=tmp->left;
                if(tmp->right) arr[++high]=tmp->right;
            }
        }
        lvl++;
    }
    return NULL;
}

void show_time(struct node* root){
    if(!root) return;
    printf("%d ",root->val);
    show_time(root->left);
    show_time(root->right);
}

int bfs(struct node* root,int lvl){
    if(lvl==-1) return 0;
    if(lvl==0) return root->val;
    struct node** arr = (struct node**)malloc(1000*sizeof(struct node*));
    int low=-1; int high=-1;
    int sum=0;
    arr[++high]=root;
    while(lvl--){
        int len=high-low;
        for(int i=0; i<len; i++){
            struct node* tmp = arr[++low];
            sum+=tmp->val;
            
            if(tmp->left) arr[++high]=tmp->left;
            if(tmp->right) arr[++high]=tmp->right;
            
        }
    }
    while(low!=high) sum+=arr[++low]->val;
    free(arr);
    return sum;
}

int dfs(struct node* root, int b){
    if(root==NULL || b==0) return 0;
    int ans = root->val;
    root->val=0;
    return ans+dfs(root->left,b-1)+dfs(root->right,b-1)+dfs(root->parent,b-1);
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
    addParent(root);

    int a,b; 
    scanf("%d %d",&a,&b);

    struct node* req = level(root,a);

    //Simple approach using DFS
    printf("%d\n",dfs(req,b+1));


    //Very long approach using BFS
    // int ans = bfs(req,b);
    // struct node*p = req->parent;
    // struct node*now = req;

    // while((p)&&(b--)){
    //     ans+=p->val;
    //     if(p->left!=now) ans+=bfs(p->left,b-1);
    //     if(p->right!=now) ans+=bfs(p->right,b-1);
    
    //     now=p;
    //     p=p->parent;
    // }
    // printf("%d\n",ans);
    deleteMemory(root);
}