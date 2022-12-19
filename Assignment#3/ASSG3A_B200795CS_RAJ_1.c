#include<stdio.h>
#include<stdlib.h>
  
struct node{
    int val;
    struct node *left;
    struct node *right;
    int height;
};
  
int height(struct node *root){
    if (!root) return 0;
    return root->height;
}

int max(int a, int b){
    if(a<b) return b;
    return a;
}
  

struct node* makeNode(int val){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->val=val;
    node->left=NULL;
    node->right=NULL;
    node->height=1;  
    return node;
}

struct node *RightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
  
    x->right = y;
    y->left = T2;
  
    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
  
    return x;
}
  

struct node *LeftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
  
    
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
  
    return y;
}
  

int bFactor(struct node *root){
    if (!root) return 0;
    return height(root->left)-height(root->right);
}
  
struct node* insert(struct node* node, int val){
    if (node == NULL) return makeNode(val);
  
    if (val<node->val) node->left=insert(node->left,val);
    else if (val>node->val) node->right=insert(node->right,val);
    else  return node;

    node->height = 1 + max(height(node->left),height(node->right));
    int balance = bFactor(node);
  
    // Left-Left
    if (balance > 1 && val < node->left->val)
        return RightRotate(node);
  
    // Right-Right
    if (balance < -1 && val > node->right->val)
        return LeftRotate(node);
  
    // Left-Right
    if (balance > 1 && val > node->left->val){
        node->left =  LeftRotate(node->left);
        return RightRotate(node);
    }

    // Right-Left
    if (balance < -1 && val < node->right->val){  
        node->right = RightRotate(node->right);
        return LeftRotate(node);
    }
    return node;
}  

struct node * predecessor(struct node* now){
    if(!now->right) return now;
    return predecessor(now->right);
}

struct node* removeNode(struct node* root, int val){
    if (root==NULL) return root;

    if (val<root->val) root->left=removeNode(root->left,val);
    else if(val>root->val) root->right=removeNode(root->right,val);   
    else{
        if((root->left==NULL)||(root->right==NULL)){
            struct node*temp=root->left?root->left:root->right;
            if (temp==NULL){
                free(root);
                return NULL;
            }
            else{
                struct node* del = root;
                root = temp; 
                free(del);
            }
        }
        else{
            struct node* temp = predecessor(root->left);
            root->val=temp->val;
            root->left = removeNode(root->left,temp->val);
        }
    }
  
    root->height = 1+max(height(root->left),height(root->right));
    int bParent = bFactor(root);
  
    if (bParent>1 && bFactor(root->left)>=0)
        return RightRotate(root);
  
    if (bParent>1 && bFactor(root->left)<0){
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    if (bParent<-1 && bFactor(root->right)<=0)
        return LeftRotate(root);
  
    if (bParent<-1 && bFactor(root->right)>0){
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }
    return root;
}

struct node* isPresent(struct node *root,int val)
{
	while(root)
	{
		if(val<root->val) root=root->left;
		else if(val>root->val) root=root->right;
		else return root;
	}
	return NULL;
} 

void printTree(struct node *root)
{
	printf("( ");
    if(root){
        printf("%d ", root->val);
        printTree(root->left);
        printTree(root->right);
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
    
    struct node* root = NULL;
    while(1){
        char ch; scanf(" %c",&ch);
        if(ch=='i'){
            int val; scanf("%d",&val);
            root=insert(root,val);
        }
        else if(ch=='p'){
            printTree(root);
            printf("\n");
        }
        else if(ch=='d'){
            int val; scanf("%d",&val);
        
            if(!isPresent(root,val)) printf("FALSE\n");
            else{
                root=removeNode(root,val);
                printf("%d\n",val);
            }
        }

        else if(ch=='s'){
            int val; scanf("%d",&val);
            if(isPresent(root,val)) printf("TRUE\n");
            else printf("FALSE\n");
        }

        else if(ch=='b'){
            int val; scanf("%d",&val);
            struct node* temp = isPresent(root,val);

			if(temp) printf("%d\n",bFactor(temp));
			else printf("FALSE\n");
        }
        else{
            deleteMemory(root);
            return 0;
        }
    }
}
