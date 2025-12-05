#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    printf("Number of processes: ");
    if(scanf("%d",&n)!=1) return 0;
    printf("Number of resource types: ");
    scanf("%d",&m);

    int i,j;
    int alloc[n][m], max[n][m], need[n][m], avail[m];
    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&alloc[i][j]);

    printf("Enter Max matrix (%d x %d):\n", n, m);
    for(i=0;i<n;i++) for(j=0;j<m;j++) scanf("%d",&max[i][j]);

    printf("Enter Available vector (%d):\n", m);
    for(j=0;j<m;j++) scanf("%d",&avail[j]);

    for(i=0;i<n;i++) for(j=0;j<m;j++){
        need[i][j] = max[i][j] - alloc[i][j];
        if(need[i][j] < 0) need[i][j] = 0;
    }

    int finish[n];
    for(i=0;i<n;i++) finish[i]=0;
    int work[m];
    for(j=0;j<m;j++) work[j]=avail[j];

    int safeSeq[n], idx=0;
    int madeProgress;
    do {
        madeProgress = 0;
        for(i=0;i<n;i++) if(!finish[i]) {
            int k;
            for(k=0;k<m;k++) if(need[i][k] > work[k]) break;
            if(k==m) { // can finish
                for(j=0;j<m;j++) work[j] += alloc[i][j];
                finish[i]=1;
                safeSeq[idx++]=i;
                madeProgress = 1;
            }
        }
    } while(madeProgress);

    int safe = 1;
    for(i=0;i<n;i++) if(!finish[i]) safe=0;

    if(safe) {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for(i=0;i<idx;i++){
            printf("P%d", safeSeq[i]);
            if(i<idx-1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }
    return 0;
}
