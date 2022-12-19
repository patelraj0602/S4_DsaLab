#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node{
    char word[100];
    struct node* next;
};

int find_hash1(char* word, int n){
    int len = strlen(word);
    if(len==1){
        int val = 2*(word[0]);
        return (val%n);
    }
    else{
        int sum = (word[0]+word[1]+word[len-2]+word[len-1])/len;
        return sum%n;
    }
}

int find_hash2(char* word, int n){
    double sum = 0;
    int len = strlen(word);
    for(int i=0; i<len; i++)
        sum+=word[i];
    sum/=len;
    int val = ceil(sum);
    return (val%n);
}

int helper(struct node* head){
    int val = 0;
    while(head){
        val++;
        head=head->next;
    }
    return val;
}

void print_table(struct node** arr, int n){
    for(int i=0; i<n; i++){
        struct node* head = arr[i];
        if(arr[i]==NULL) printf("NULL\n");
        else{
            while(head){
                printf("%s ", head->word);
                head=head->next;
            }
            printf("\n");
        }
    }
}


void store_word(struct node** arr, int n, char* w){
    int val1 = find_hash1(w,n);
    int val2 = find_hash2(w,n);

    int num1 = helper(arr[val1]);
    int num2 = helper(arr[val2]);

    struct node* now = (struct node*)malloc(sizeof(struct node));
    strcpy(now->word, w);
    now->next = NULL;

    if(num2 < num1){
        struct node* head = arr[val2];
        if(head==NULL) arr[val2]=now;
        else{
            while(head->next) head=head->next;
            head->next = now;
        }
    }
    else{
        struct node* head = arr[val1];
        if(head==NULL) arr[val1]=now;
        else{
            while(head->next) head=head->next;
            head->next = now;
        }
    }
}



int main(){
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    
    int n; scanf("%d",&n);
    struct node** arr = (struct node**)malloc(n*sizeof(struct node*));
    for(int i=0; i<n; i++)
        arr[i]=NULL;
    

    char s[500000];
    scanf(" %[^\n]%*c", s);
    int len = strlen(s);

    int i=0;
    while(i<len){
        char tmp[50]; int j=0;
        while((i<len)&&(s[i]!=' '))
            tmp[j++]=s[i++];
            
        tmp[j]='\0'; i++;

        store_word(arr,n,tmp);
    }
    print_table(arr,n);

    //Freeing memory
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
