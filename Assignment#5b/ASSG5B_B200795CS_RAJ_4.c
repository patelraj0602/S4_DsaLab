#include <stdio.h>
#include <stdlib.h>

struct GraphEdge{
    int s;
    int d;
    int wt;
};

int main(){
    // #ifndef ONLINE_JUDGE 
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    int v,e;
    scanf("%d %d",&v,&e);

    struct GraphEdge** edges = (struct GraphEdge**)malloc(e*sizeof(struct GraphEdge*));
    for(int i=0; i<e; i++)
        edges[i] = (struct GraphEdge*)malloc(sizeof(struct GraphEdge));

    for(int i=0; i<e; i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        edges[i]->s = a;
        edges[i]->d = b;
        edges[i]->wt = c;
    }

    // checkNegativeCycle(edges,0,v,e);
    // Working Here
    int max = 100000000;
    int distance[v];
    for(int i=0; i<v; i++) distance[i]=max;
    distance[0]=0;

    for(int i=0; i<v-1; i++)
        for(int j=0; j<e; j++)
            if((distance[edges[j]->s] != max)&&(distance[edges[j]->s]+edges[j]->wt < distance[edges[j]->d]))
                distance[edges[j]->d] = distance[edges[j]->s] + edges[j]->wt;

    int val=0;
    for(int i=0; i<e; i++){
        if((distance[edges[i]->s]!=max) && (distance[edges[i]->s] + edges[i]->wt < distance[edges[i]->d])){
            val=1;
            break;
        }
    }
    if(val) printf("1\n");
    else printf("-1\n");

    for(int i=0; i<e; i++)
        free(edges[i]);
    free(edges);
}