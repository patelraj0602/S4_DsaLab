#include <stdio.h>

int main(){
    // #ifndef ONLINE_JUDGE 
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif
    
    int n; scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("%d ",i);
        for(int j=0; j<n; j++){
            int temp; scanf("%d",&temp);
            if(temp) printf("%d ",j);
        }
        printf("\n");
    }
}