/*
 worst_fit.c
 Implements Worst Fit memory allocation:
  - Reads number of holes and their sizes
  - Reads number of processes and their sizes
  - Allocates each process to the largest hole that fits (worst fit)
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
        int maxSize = INT_MIN;
        for (int j = 0; j < h; ++j) {
            if (holes[j] >= proc[i]) {
                if (holes[j] > maxSize) {
                    maxSize = holes[j];
                    chosen = j;
                }
            }
        }
        if (chosen != -1) {
            alloc[i] = chosen;       // allocate process i to hole chosen
            holes[chosen] -= proc[i]; // reduce hole size
        }
    }

    printf("\nAllocation (process -> hole index) or -1 if not allocated:\n");
    for (int i = 0; i < p; ++i) {
        printf("P%d (%d) -> %d\n", i, proc[i], alloc[i]);
    }
    return 0;
}
