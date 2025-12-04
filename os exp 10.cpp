/* page_lru.c
   LRU page replacement with hardcoded input.
   Compile: gcc page_lru.c -o page_lru && ./page_lru
*/

#include <stdio.h>
#include <limits.h>

int main() {
    int frames = 3;
    int ref[] = {1,2,3,4,1,2,5,1,2,3,4,5};
    int n = sizeof(ref)/sizeof(ref[0]);

    int frame[3], lastUsed[3];
    for (int i=0;i<frames;i++){ frame[i] = -1; lastUsed[i] = -1; }
    int time = 0, faults = 0;

    printf("LRU Page Replacement (frames=%d)\n", frames);
    for (int i=0;i<n;i++) {
        int page = ref[i];
        int found = -1;
        for (int j=0;j<frames;j++) if (frame[j]==page) { found = j; break; }

        if (found != -1) {
            lastUsed[found] = time++;
            printf("Ref %d -> hit; frames: ", page);
        } else {
            int empty = -1;
            for (int j=0;j<frames;j++) if (frame[j]==-1) { empty = j; break; }
            if (empty != -1) {
                frame[empty] = page;
                lastUsed[empty] = time++;
            } else {
                int lru = 0;
                for (int j=1;j<frames;j++) if (lastUsed[j] < lastUsed[lru]) lru = j;
                frame[lru] = page;
                lastUsed[lru] = time++;
            }
            faults++;
            printf("Ref %d -> page fault; frames: ", page);
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
