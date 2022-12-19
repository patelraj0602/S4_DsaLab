#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    char name[50];
    struct node* next;
};

// To find the hash_val.
int hash_value(char* name, int n){
    int len = strlen(name);

    int val = 0;
    for(int i=len-1; i>=0; i--){
        if((name[i]>=65) && (name[i]<=90))
            val = (val*3)+(name[i]-'A'+1);
        else
            val = (val*3)+(name[i]-'a'+1);
    }
    return val%n;
}

// For debugging purpose
void printer(struct node** arr, int n){
    for(int i=0; i<n; i++){
        printf("%d : ",i);
        struct node* head = arr[i];
        while(head){
            printf("%s ",head->name);
            head=head->next;
        }
        printf("\n");
    }
    printf("\n");
}

// Inserting the element from the hash table.
int insert(struct node** arr, char* name, int n){
    struct node* now = (struct node*)malloc(sizeof(struct node));
    strcpy(now->name, name);
    now->next = NULL;

    int val = hash_value(name, n);
    now->next = arr[val];
    arr[val] = now;
}

//Removing the element from the hash table.
void delele_val(struct node** arr, char* name, int n){
    int val = hash_value(name, n);

    struct node* pre = NULL;
    struct node* head = arr[val];
    while(head){
        if(strcmp(head->name, name)==0){
            if(pre==NULL) arr[val]=head->next;
            else pre->next = head->next;

            free(head);
            return;
        }

        pre = head;
        head = head->next;
    }
}

int check(struct node** arr, int n){
    for(int i=0; i<n; i++){
        if(arr[i]==NULL) continue;
        else{
            if(arr[i]->next) 
                return -1;
        }
    }
    return 1;
}

// To free the dynamically allocated memory.
void cleaner(struct node** arr, int n){
    for(int i=0; i<n; i++){
        struct node* head = arr[i];
        while(head){
            struct node* tmp = head;
            head=head->next;
            free(tmp);
        }
    }
    free(arr);
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout);
    #endif
    
    int n; scanf("%d",&n);
    struct node** arr = (struct node**)malloc(n*sizeof(struct node*));

    for(int i=0; i<n; i++)
        arr[i]=NULL;

    while(1){
        char ch; scanf(" %c", &ch);

        if(ch=='i'){
            char name[50];
            scanf("%s", name);
            insert(arr, name, n);
        }
        else if(ch=='d'){
            char name[50];
            scanf("%s", name);
            delele_val(arr, name, n);
        }
        else if(ch=='p'){
            int val = check(arr,n);
            printf("%d\n",val);
        }
        else{
            cleaner(arr,n);
            return 0;
        }
    }
}
