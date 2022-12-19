#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student{
    char name[50];
    int isPresent;
};

struct student** arr;

int hashFun(char* name){
    int len = strlen(name);
    int val=0;

    int temp=0;
    temp+=(0<=len?(int)name[0]:0);
    temp+=(1<=len?(int)name[1]:0);
    temp+=(2<=len?(int)name[2]:0);
    val+=(100*((temp%26)%10));

    temp=0;
    temp+=(0<=len?(int)name[0]:0);
    temp+=(2<=len?(int)name[2]:0);
    temp+=(4<=len?(int)name[4]:0);
    val+=(10*((temp%26)%10));

    temp=0;
    temp+=(0<=len?(int)name[0]:0);
    temp+=(4<=len?(int)name[4]:0);
    temp+=(8<=len?(int)name[8]:0);
    val+=((temp%26)%10);

    return val;
}

void insertData(char* name){
    int val = hashFun(name);
    strcpy(arr[val]->name,name);
    arr[val]->isPresent=1;
}

void searchData(char* rn){
    int len = strlen(rn);
    int val = 0;
    for(int i=1; i<len; i++) 
        val=((val*10)+(rn[i]-'0'));
    
    if(arr[val]->isPresent) printf("%s\n",arr[val]->name);
    else printf("NOT FOUND\n");
}

void deleteData(char* rn){
    int len = strlen(rn);
    int val = 0;
    for(int i=1; i<len; i++) 
        val=((val*10)+(rn[i]-'0'));

    arr[val]->isPresent=0;
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    

    arr = (struct student**)malloc(1000*sizeof(struct student*));
    for(int i=0; i<1000; i++){
        struct student* now = (struct student*)malloc(sizeof(struct student));
        now->isPresent=0;
        arr[i]=now;
    }

    while(1){
        char c; scanf(" %c",&c);
        if(c=='i'){
            char name[50]; scanf(" %s",name);
            insertData(name);
        }
        else if(c=='s'){
            char rn[50]; scanf(" %s",rn);
            searchData(rn);
        }
        else if(c=='d'){
            char rn[50]; scanf(" %s",rn);
            deleteData(rn);
        }
        else{
            for(int i=0; i<1000; i++) free(arr[i]);
            free(arr);
            return 0;
        }
    }
}