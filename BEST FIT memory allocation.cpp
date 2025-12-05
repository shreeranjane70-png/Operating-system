/*
 best_fit.c
 Implements Best Fit memory allocation:
  - Reads number of holes and their sizes
  - Reads number of processes and their sizes
  - Allocates each process to the smallest hole that is >= process size (best fit)
  - Prints allocation (hole index) or -1 if not allocated
*/

#include <stdio.h>
#include <limits.h>

int main() {
    int h, p;
    printf("Number of memory holes: ");
    if (scanf("%d", &h) != 1) return 0;

    int holes[h];
    printf("Enter hole sizes (space separated):\n");
    for (int i = 0; i < h; ++i) scanf("%d", &holes[i]);

    printf("Number of processes: ");
    scanf("%d", &p);
    int proc[p];
    printf("Enter process sizes (space separated):\n");
    for (int i = 0; i < p; ++i) scanf("%d", &proc[i]);

    int alloc[p];
    for (int i = 0; i < p; ++i) alloc[i] = -1;

    for (int i = 0; i < p; ++i) {
        int chosen = -1;
        int bestDiff = INT_MAX;
        for (int j = 0; j < h; ++j) {
            if (holes[j] >= proc[i]) {
                int diff = holes[j] - proc[i];
                if (diff < bestDiff) {
                    bestDiff = diff;
                    chosen = j;
                }
            }
        }
        if (chosen != -1) {
            alloc[i] = chosen;
            holes[chosen] -= proc[i];
        }
    }

    printf("\nAllocation (process -> hole index) or -1 if not allocated:\n");
    for (int i = 0; i < p; ++i) {
        printf("P%d (%d) -> %d\n", i, proc[i], alloc[i]);
    }
    return 0;
}
