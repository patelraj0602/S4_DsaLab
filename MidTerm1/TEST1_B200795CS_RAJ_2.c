// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

// struct node{
//     char id[150];
//     int val;
//     struct node* left;
//     struct node* right;
// };


// void deleteMemory(struct node* root){
//     if(root==NULL) return;
//     deleteMemory(root->left);
//     deleteMemory(root->right);
//     free(root);
// }


// struct node* make_tree(char* s, int low, int high){
//     if(s[low+2]==')') return NULL;
//     low++;

//     char id[150]; int j=0;
//     while(s[++low]!=' ') id[j++]=s[low];
//     id[j]='\0';

//     int num=0;
//     while(s[++low]!=' ') num = (num*10)+(s[low]-'0');
//     low++;

//     struct node* now = (struct node*)malloc(sizeof(struct node));
//     strcpy(now->id, id);
//     now->val=num;

//     int mid = low+1;
//     int tmp=1;
//     while(tmp){
//         if(s[mid]=='(') tmp++;
//         else if(s[mid]==')') tmp--;
//         mid++;
//     }

//     now->left = make_tree(s,low,mid-1);
//     now->right = make_tree(s,mid+1, high-2);
//     return now;
// }

// void print_employees(struct node* root){
//     if(root==NULL) return;

//     print_employees(root->left);
//     print_employees(root->right);
//     printf("%s ",root->id);
// }


// struct node* read_and_store(){
//     char s[100005];
//     scanf("%[^\n]%*c", s);
//     int len = strlen(s);

//     struct node* root = make_tree(s,0,len-1);
//     return root;
// }

// int find_employees(struct node* root){
//     if(root==NULL) return 0;

//     int val = find_employees(root->left)+find_employees(root->right);
    
//     if(root->val == val) {
//         if(root->left==NULL && root->right==NULL) return 0;
//         else printf("%s ", root->id);
//     }
//     return val+root->val;
// }


// int main(){
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif
    
//     // Creating a tree.
//     struct node* root = read_and_store();

//     // Printing a tree
//     print_employees(root);
//     printf("\n");

//     //Finding employee
//     int gar = find_employees(root);
//     printf("\n");

//     //Freeing memory
//     deleteMemory(root);

// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    char id[150];
    int val;
    struct node* left;
    struct node* right;
};


void deleteMemory(struct node* root){
    if(root==NULL) return;
    deleteMemory(root->left);
    deleteMemory(root->right);
    free(root);
}


struct node* make_tree(char* s, int low, int high){
    if(s[low+2]==')') return NULL;
    low++;

    char id[150]; int j=0;
    while(s[++low]!=' ') id[j++]=s[low];
    id[j]='\0';

    int num=0;
    while(s[++low]!=' ') num = (num*10)+(s[low]-'0');
    low++;

    struct node* now = (struct node*)malloc(sizeof(struct node));
    strcpy(now->id, id);
    now->val=num;

    int mid = low+1;
    int tmp=1;
    while(tmp){
        if(s[mid]=='(') tmp++;
        else if(s[mid]==')') tmp--;
        mid++;
    }

    now->left = make_tree(s,low,mid-1);
    now->right = make_tree(s,mid+1, high-2);
    return now;
}

void print_employees(struct node* root){
    if(root==NULL) return;

    print_employees(root->left);
    print_employees(root->right);
    printf("%s ",root->id);
}


struct node* read_and_store(){
    char s[100005];
    scanf("%[^\n]%*c", s);
    int len = strlen(s);

    struct node* root = make_tree(s,0,len-1);
    return root;
}

int find_employees(struct node* root){
    if(root==NULL) return 0;

    int val = find_employees(root->left)+find_employees(root->right);
    
    if(root->val == val) {
        if(root->left==NULL && root->right==NULL) return 0;
        else printf("%s ", root->id);
    }
    return val+root->val;
}


int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    // Creating a tree.
    struct node* root = read_and_store();

    // Printing a tree
    print_employees(root);
    printf("\n");

    //Finding employee
    int gar = find_employees(root);
    printf("\n");

    //Freeing memory
    deleteMemory(root);

}