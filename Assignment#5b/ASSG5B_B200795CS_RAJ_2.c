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

// For Kruskal's algorithm.
void swap(struct node** arr, int a, int b){
    struct node* temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

void sorting(struct node** arr, int n){
   int i, j;
   for (i = 0; i < n-1; i++)     
       for (j = 0; j < n-i-1; j++)
           if (arr[j]->weight > arr[j+1]->weight)
              swap(arr,j,j+1);
}

void makeSet(int val, int* parent, int* rank){
    parent[val] = val;
    rank[val]=0;
}

int findSet(int val, int* parent){
    if(val==parent[val]) return val;
    return parent[val] = findSet(parent[val], parent);
}

int rankUnionSet(int a, int b, int* parent, int* rank){
    a = findSet(a, parent);
    b = findSet(b, parent);

    if(a==b) return 0;
    if(rank[a] < rank[b]) {
        parent[a]=b;
        return 1;
    }
    
    if(rank[a]==rank[b]) rank[a]++;
    parent[b]=a;
    return 1;
}

void kruskals(struct list** graph, int n){
    struct node* arr[1000]; int len=0;
    for(int i=0; i<n; i++){
        struct list* now = graph[i];
        while(now){
            struct node* temp = (struct node*)malloc(sizeof(struct node));
            temp->start=i;
            temp->end=now->index;
            temp->weight=now->weight;
            arr[len]=temp; len++;
            now=now->next;
        }
    }
    sorting(arr,len);
    // for(int i=0; i<len; i++) printf("%d %d %d\n",arr[i]->start,arr[i]->end,arr[i]->weight);

    int parent[n]; int rank[n];
    for(int i=0; i<n; i++) makeSet(i,parent,rank);

    int sum=0;
    for(int i=0; i<len; i++){
        int start = arr[i]->start;
        int end = arr[i]->end;
        if(rankUnionSet(start,end,parent,rank))
            sum+=arr[i]->weight;
    }
    printf("%d\n",sum);

    //Freeing Memory
    for(int i=0; i<len; i++) free(arr[i]);
}


// For Prims's algorithm
int minimumIndex(int* minCost, int* visited, int n){
    int max = 100000000; int index = -1;
    for(int i=0; i<n; i++){
        if((!visited[i])&&(minCost[i]<max)){
            max = minCost[i];
            index = i;
        }
    }
    return index;
}

// Again to optimize this we need decrease key function of priority queue.
void primMST(struct list** graph, int n){
    int max = 100000000;
    int minCost[n];
    int visited[n];
    for(int i=0; i<n; i++) visited[i]=0;
    for(int i=0; i<n; i++) minCost[i]=max;

    minCost[0]=0;
    for(int i=0; i<n-1; i++){
        int minIndex = minimumIndex(minCost,visited,n);
        visited[minIndex]=1;
        struct list* now = graph[minIndex];
        while(now){
            if((!visited[now->index])&&(minCost[now->index] > now->weight))
                minCost[now->index]=now->weight;
            now=now->next;
        }
    }
    int minimumSum=0;
    for(int i=0; i<n; i++) minimumSum+=minCost[i];
    printf("%d\n",minimumSum);
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
        struct list* now = graph[i];
        while(now){
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

    char c; scanf("%c",&c);
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

    if(c=='a') kruskals(graph,n);
    else primMST(graph,n);

    //Freeing Memory
    freeingMemory(graph,n);
}