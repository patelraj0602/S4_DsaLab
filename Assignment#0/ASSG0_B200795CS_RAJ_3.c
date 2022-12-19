#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list{
    int val;
    struct list* next;
};

void createNode(struct list** pt, int val){
    struct list* now = (struct list*)malloc(sizeof(struct list));
    now->val = val;
    now->next = NULL;

    if(*pt) (*pt)->next = now;
    *pt = now;
}

void freeing(struct list* head){
    while(head!=NULL){
        struct list* del = head;
        head=head->next;
        free(del);
    }
}

int main(){
    struct list* head = NULL;
    struct list* tmp = NULL;

    int noNodes = 0;
    char num[10000]; char str[10];
    scanf("%[^\n]%*c", num);
    scanf("%[^\n]%*c", str);

    int len = strlen(num);
    for(int j=0; j<len; j++){
        int nn = 0;
        while(j<len && num[j]!=' '){
            nn = (nn*10)+(num[j]-'0');
            j++;        
        }
        noNodes++;
        createNode(&tmp,nn);
        if(!head) head=tmp;
    }

    int index = 0; int j=0;
    len = strlen(str);
    while(j<len) {
        index=(index*10)+(str[j]-'0');
        j++;
    }
    struct list* f = head;
    if(index > noNodes)
        printf("-1\n");
    else{
        int req = noNodes-index+1;
        while(--req) head=head->next;
        printf("%d\n",head->val);
    }
    freeing(f);
}