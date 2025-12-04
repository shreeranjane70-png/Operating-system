#include <stdio.h>

int main() {
    // Sample data (change if you want)
    int n = 5; // processes P0..P4
    int m = 3; // resource types R0..R2

    int alloc[5][3] = {
        {0, 1, 0}, // P0
        {2, 0, 0}, // P1
        {3, 0, 2}, // P2
        {2, 1, 1}, // P3
        {0, 0, 2}  // P4
    };

    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[3] = {3, 3, 2}; // Available vector

    int need[5][3];
    for (int i=0;i<n;i++) for (int j=0;j<m;j++) need[i][j] = max[i][j] - alloc[i][j];

    int finish[5] = {0};
    int work[3];
    for (int j=0;j<m;j++) work[j] = avail[j];

    int safeSeq[5], idx = 0;
    int progress;
    do {
        progress = 0;
        for (int i=0;i<n;i++) {
            if (!finish[i]) {
                int j;
                for (j=0;j<m;j++) if (need[i][j] > work[j]) break;
                if (j==m) {
                    for (int k=0;k<m;k++) work[k] += alloc[i][k];
                    finish[i] = 1;
                    safeSeq[idx++] = i;
                    progress = 1;
                }
            }
        }
    } while(progress);

    int safe = 1;
    for (int i=0;i<n;i++) if (!finish[i]) safe = 0;

    printf("Banker's algorithm - hardcoded sample\n");
    if (safe) {
        printf("System is in a SAFE state.\nSafe sequence: ");
        for (int i=0;i<idx;i++) {
            printf("P%d", safeSeq[i]);
            if (i<idx-1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    return 0;
}
