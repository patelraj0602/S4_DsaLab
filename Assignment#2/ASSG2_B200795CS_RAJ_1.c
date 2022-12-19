#include <stdio.h>
#include <stdlib.h>

char c;
int c1,c2,len,R;

//To find largest prime.
int lPrime(int len){
    for(int i=len-1; i>=2; i--){
        int flag=1;
        for(int j=2; j*j<=i; j++){
            if(!(i%j)){
                flag=0; 
                break;
            }            
        }
        if(flag) return i;
    }
}

//Inserting into hash table
void insert(int* arr, int k){
    int a = k%len;
    for(int i=0; i<len; i++){
        int val = (c=='a') ? (a+(i*c1)+(i*i*c2))%len : (a+(i*(R-(k%R))))%len;
        if((arr[val]==-1)||(arr[val]==-2)){
            arr[val]=k;
            return;
        }
    }
}

//Searching in hash table
int search(int* arr, int k){
    int a = k%len;
    for(int i=0; i<len; i++){
        int val = (c=='a') ? (a+(i*c1)+(i*i*c2))%len : (a+(i*(R-(k%R))))%len;
        if(arr[val]==k) return 1;
        else if(arr[val]==-1) return -1;
        else continue;
    }
    return -1;
}

//Deleting from hash table
void delete(int* arr, int k){
    int a = k%len;
    for(int i=0; i<len; i++){
        int val = (c=='a') ? (a+(i*c1)+(i*i*c2))%len : (a+(i*(R-(k%R))))%len;
        if(arr[val]==k) {
            arr[val]=-2;
            return;
        }
    }
}

//Making an hash table which is essentially an array.
int* makeTable(int len){
    int* arr = (int*)malloc(len*sizeof(int));
    for(int i=0; i<len; i++) arr[i]=-1;
    return arr;
}

//Printing content
void print(int* arr){
    for(int i=0; i<len; i++){
        printf("%d ",i);
        if(arr[i]>=0) printf("(%d)\n",arr[i]);
        else printf("()\n");
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    scanf("%c %d",&c,&len);

    if(len<=2 && c=='b'){
        printf("AlerT! Wrong test case");
        return 0;
    }

    int* arr = makeTable(len);

    if(c=='a') scanf("%d %d",&c1,&c2);
    else  R = lPrime(len);

    while(1){
        char ch; scanf(" %c",&ch);
        if(ch=='i'){
            int k; scanf("%d",&k);
            insert(arr,k);
        }
        else if(ch=='s'){
            int k; scanf("%d",&k);
            printf("%d\n",search(arr,k));            
        }
        else if(ch=='d'){
            int k; scanf("%d",&k);
            delete(arr,k);
        }
        else if(ch=='p'){
            print(arr);
        }
        else{
            free(arr);
            return 0;
        }
    }
}


