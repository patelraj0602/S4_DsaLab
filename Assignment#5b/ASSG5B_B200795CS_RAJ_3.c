#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    int weight;
    int start; 
    int end;
};

struct list{
    int index;
    int weight;
    struct list* next;
};

void dHelp(int i, int* visited, struct list** graph, int n, int* md){
    visited[i]=1;
    struct list* now = graph[i];
    while(now){
        if((now->weight+md[i]) < md[now->index])
            md[now->index]=md[i]+now->weight;
        now=now->next;
    }
    return;
}

int extractMinIndex(int* md, int n, int* visited){
    int index = -1;
    int val = 1000000000;
    for(int i=0; i<n; i++){
        if((md[i]<val)&&(!visited[i])){
            index=i;
            val=md[i];
        }
    }
    return index;
}

int* dijkstra(int n, struct list** graph, int s){
    int max = 100000000;
    int* minDistance = (int*)malloc(n*sizeof(int));
    int visited[n];
    for(int i=0; i<n; i++){
        minDistance[i] = max;
        visited[i]=0;
    }

    minDistance[s]=0;
    for(int i=0; i<n; i++){
        int index = extractMinIndex(minDistance,n,visited);
        dHelp(index,visited,graph,n,minDistance);
    }
    return minDistance;
}

void helpDijkstra(int n, struct list** graph){
    int max = 100000000;
    while(1){
        char str[100]; scanf(" %s",str);
        if(strcmp(str,"stop")==0) return;
        else if(strcmp(str,"apsp")==0){
            int val; scanf("%d",&val);
            int* arr = dijkstra(n,graph,val);
            for(int i=0; i<n; i++){
                if(arr[i]==max) printf("UNREACHABLE ");
                else printf("%d ",arr[i]);
            }
            printf("\n");
            free(arr);
        }
        else{
            int a,b;
            scanf("%d %d\n",&a,&b);
            int* arr = dijkstra(n,graph,a);
            if(arr[b]==max) printf("UNREACHABLE");
            else printf("%d\n",arr[b]);
            free(arr);
        }
    }
}

// Making a map.
int findInteger(char* str, int* i, int len){
    int val = 0;
    while(((*i)+1<len)&&(str[++(*i)]!=' ')) val=(val*10)+(str[(*i)]-'0');
    return val;
}

struct list* createNode(int val){
    struct list* now = (struct list*)malloc(sizeof(struct list));
    now->index = val;
    now->next=NULL;
    return now;
}

void freeingMemory(struct list** graph, int n){
    for(int i=0; i<n; i++){
        // printf("Adjacent Value of node %d is : \n",i);
        struct list* now = graph[i];
        while(now){
            // printf("%d %d\n",now->index, now->weight);
            struct list* del = now;
            now=now->next;
            free(del);
        }
    }
    free(graph);
}

int main(){
    // #ifndef ONLINE_JUDGE 
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    int n; scanf(" %d",&n);
    
    struct list** graph = (struct list**)malloc(n*sizeof(struct list*));
    for(int i=0; i<n; i++)
        graph[i]=NULL;
        
    for(int j=0; j<n; j++){
        char str[1000];
        scanf(" %[^\n]s", str);
        int i=-1; int len=strlen(str);
        
        int index = findInteger(str,&i,len);
        struct list* adjacent = graph[index];
        while(i+1<len){
            int val = findInteger(str,&i,len);
            struct list* now = createNode(val);
            if(!adjacent){
                adjacent=now;
                graph[index]=now;
            }
            else{
                adjacent->next=now;
                adjacent=adjacent->next;
            }
        }
    }
    for(int j=0; j<n; j++){
        char str[1000];
        scanf(" %[^\n]s", str);
        int i=-1; int len=strlen(str);

        int index = findInteger(str,&i,len);
        struct list* now = graph[index];
        while(i+1<len){
            int weight = findInteger(str,&i,len);
            now->weight=weight;
            now=now->next;
        }
    }
    helpDijkstra(n,graph);

    //Freeing Memory
    freeingMemory(graph,n);
}