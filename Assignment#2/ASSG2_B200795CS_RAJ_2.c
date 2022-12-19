#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char word[50];
    struct node* next;
};

int main(){
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    int m; scanf("%d",&m);

    char s[501];
    scanf(" %[^\n]%*c", s);
    int len = strlen(s);

    struct node** arr = (struct node**)malloc(m*sizeof(struct node*));
    for(int i=0; i<m; i++) arr[i]=NULL;

    int i=0;
    while(i<len){
        char tmp[50]; int j=0;
        while((i<len)&&(s[i]!=' '))
            tmp[j++]=s[i++];
            
        tmp[j]='\0'; i++;

        int ll = strlen(tmp);
        int val = (ll*ll)%m;

        struct node* head = arr[val];
        struct node* pre = NULL;

        int flag=0;
        while(head){
            if(strcmp(head->word, tmp)==0){
                flag=1;
                break;
            }
            pre=head;
            head=head->next;
        }
        if(flag) continue;

        struct node* now = (struct node*)malloc(sizeof(struct node));
        now->next=NULL;
        strcpy(now->word, tmp);

        if(pre) pre->next=now;
        else arr[val]=now;
    }

    //Printing
    for(int i=0; i<m; i++){
        printf("%d:",i);
        struct node* head = arr[i];

        if(!head) printf("null\n");
        else{
            while(head){
                printf("%s",head->word);
                if(head->next) printf("-");
                head=head->next;
            }
            printf("\n");
        }
    }

    //Freeing memory
    for(int i=0; i<m; i++){
        struct node* head = arr[i];
        while(head){
            struct node* tmp = head;
            head=head->next;
            free(tmp);
        }
    }
    free(arr);
}
