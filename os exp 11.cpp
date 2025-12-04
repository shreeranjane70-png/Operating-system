/* page_optimal.c
   Optimal page replacement with hardcoded input.
   Compile: gcc page_optimal.c -o page_optimal && ./page_optimal
*/

#include <stdio.h>
#include <limits.h>

int findVictim(int frame[], int frames, int ref[], int n, int cur) {
    int farthest = -1, victim = -1;
    for (int i=0;i<frames;i++) {
        int j;
        for (j = cur+1; j<n; j++) if (frame[i] == ref[j]) break;
        if (j == n) return i; // not used again -> best victim
        if (j > farthest) { farthest = j; victim = i; }
    }
    return victim;
}

int main() {
    int frames = 3;
    int ref[] = {7,0,1,2,0,3,0,4,2};
    int n = sizeof(ref)/sizeof(ref[0]);
    int frame[3];
    for (int i=0;i<frames;i++) frame[i] = -1;
    int filled = 0, faults = 0;

    printf("Optimal Page Replacement (frames=%d)\n", frames);
    for (int i=0;i<n;i++) {
        int page = ref[i];
        int hit = 0;
        for (int j=0;j<frames;j++) if (frame[j]==page) { hit = 1; break; }
        if (!hit) {
            if (filled < frames) {
                frame[filled++] = page;
            } else {
                int v = findVictim(frame, frames, ref, n, i);
                frame[v] = page;
            }
            faults++;
            printf("Ref %d -> page fault; frames: ", page);
        } else {
            printf("Ref %d -> hit; frames: ", page);
        }
        for (int j=0;j<frames;j++) {
            if (frame[j]==-1) printf("- ");
            else printf("%d ", frame[j]);
        }
        printf("\n");
    }
    printf("Total page faults = %d\n", faults);
    return 0;
}
