#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int searchNode(struct node* root, int k){
    if(root==NULL) return 0;
    if(root->val==k) return 1;

    int inLeft = searchNode(root->left,k);
    if(inLeft) return 1;

    int inRight = searchNode(root->right,k);
    return inRight;
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

    int a,b; scanf("%d %d",&a,&b);

    struct node* check = root;
    int ans;
    while(check){
        ans = check->val;
        if(searchNode(check->left,a) && searchNode(check->left,b)) check=check->left;        
        else if(searchNode(check->right,a) && searchNode(check->right,b)) check=check->right;
        else break;
    }
    printf("%d\n",ans);
    deleteMemory(root);
}