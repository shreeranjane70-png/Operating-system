/* first_fit.c
   First Fit allocation with hardcoded holes and processes.
   Compile: gcc first_fit.c -o first_fit && ./first_fit
*/

#include <stdio.h>

int main() {
    int holes[] = {100, 500, 200, 300, 600};
    int h = sizeof(holes)/sizeof(holes[0]);
    int proc[] = {212, 417, 112, 426};
    int p = sizeof(proc)/sizeof(proc[0]);

    int alloc[10];
    for (int i=0;i<p;i++) alloc[i] = -1;

    for (int i=0;i<p;i++) {
        for (int j=0;j<h;j++) {
            if (holes[j] >= proc[i]) {
                alloc[i] = j;
                holes[j] -= proc[i];
                break;
            }
        }
    }

    printf("First Fit Allocation (process -> hole index or -1):\n");
    for (int i=0;i<p;i++) printf("P%d (%d) -> %d\n", i, proc[i], alloc[i]);
    return 0;
}
