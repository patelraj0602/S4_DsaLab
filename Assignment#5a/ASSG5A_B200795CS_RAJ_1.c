#include <stdio.h>
#include <stdlib.h>

void simpleMakeSet(int val, int* parent){
    parent[val] = val;
}

void rankMakeSet(int val, int* parent, int* rank){
    parent[val] = val;
    rank[val]=0;
}

int simpleFindSet(int val, int* parent, int* no_find_set){
    (*no_find_set)++;
    if(val==parent[val]) return val;
    return simpleFindSet(parent[val], parent, no_find_set);
}

int compressFindSet(int val, int* parent, int* no_find_set){
    (*no_find_set)++;
    if(val==parent[val]) return val;
    return parent[val] = compressFindSet(parent[val], parent, no_find_set);
}

int simpleUnionSetsWithoutCompress(int a, int b, int* parent, int* no_find_set){
    a = simpleFindSet(a, parent, no_find_set);
    b = simpleFindSet(b, parent, no_find_set);

    if(a!=b) parent[b]=a;
    return a;
}

int simpleUnionSetsWithCompress(int a, int b, int* parent, int* no_find_set){
    a = compressFindSet(a, parent, no_find_set);
    b = compressFindSet(b, parent, no_find_set);

    if(a!=b)  parent[b]=a;
    return a;
}

int rankUnionSetsWithoutCompress(int a, int b, int* parent, int* rank, int* no_find_set){
    a = simpleFindSet(a, parent, no_find_set);
    b = simpleFindSet(b, parent, no_find_set);

    if(a==b) return a;
    if(rank[a] < rank[b]) {
        parent[a]=b;
        return b;
    }
    
    if(rank[a]==rank[b]) rank[a]++;
    parent[b]=a;
    return a;
}

int rankUnionSetsWithCompress(int a, int b, int* parent, int* rank, int* no_find_set){
    a = compressFindSet(a, parent, no_find_set);
    b = compressFindSet(b, parent, no_find_set);

    if(a==b) return a;
    if(rank[a] < rank[b]) {
        parent[a]=b;
        return b;
    }

    if(rank[a]==rank[b]) rank[a]++;
    parent[b]=a;
    return a;
}


int main(){
    // #ifndef ONLINE_JUDGE 
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    
    int wrwc[10000];
    int wrc[10000];
    int rwc[10000]; int rwcRank[10000];
    int rc[10000]; int rcRank[10000];

    for(int i=0; i<10000; i++){
        wrwc[i]=-1;
        wrc[i]=-1;
        rwc[i]=-1;
        rc[i]=-1;
    }
    int wrwcVal=0; int wrcVal=0; int rwcVal=0; int rcVal=0;

    while(1){
        char ch; scanf(" %c",&ch);
        if(ch=='m'){
            int val; scanf("%d",&val);
            if(wrwc[val]!=-1) printf("-1\n");
            else{
                printf("%d\n",val);
                simpleMakeSet(val,wrwc);
                simpleMakeSet(val,wrc);
                rankMakeSet(val,rwc,rwcRank);
                rankMakeSet(val,rc,rcRank);
            }
        }
        else if(ch=='u'){
            int a,b; scanf("%d %d",&a,&b);
            if((wrwc[a]==-1)||(wrwc[b]==-1)) printf("-1\n");
            else{
                int p = simpleUnionSetsWithoutCompress(a,b,wrwc,&wrwcVal);
                int q = simpleUnionSetsWithCompress(a,b,wrc,&wrcVal);
                int r = rankUnionSetsWithoutCompress(a,b,rwc,rwcRank,&rwcVal);
                int s = rankUnionSetsWithCompress(a,b,rc,rcRank,&rcVal);
                printf("%d %d %d %d\n",p,r,q,s);
            }
        }
        else if(ch=='f'){
            int val; scanf("%d",&val);
            if(wrwc[val]==-1) printf("-1\n");
            else{
                int p = simpleFindSet(val,wrwc,&wrwcVal);
                int q = compressFindSet(val,wrc,&wrcVal);
                int r = simpleFindSet(val,rwc,&rwcVal);
                int s = compressFindSet(val,rc,&rcVal);
                printf("%d %d %d %d\n",p,r,q,s);
            }
        }
        else{
            printf("%d %d %d %d\n",wrwcVal,rwcVal,wrcVal,rcVal);
            return 0;
        }
    }
}