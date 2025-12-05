/* page_fifo.c
   FIFO page replacement with hardcoded input.
   Compile: gcc page_fifo.c -o page_fifo && ./page_fifo
*/

#include <stdio.h>

int main() {
    int frames = 3;
    int ref[] = {1, 2, 3, 2, 4, 1, 3};
    int n = sizeof(ref)/sizeof(ref[0]);

    int frame[3];
    for (int i=0;i<frames;i++) frame[i] = -1;
    int front = 0, faults = 0;

    printf("FIFO Page Replacement (frames=%d)\n", frames);
    for (int i=0;i<n;i++) {
        int page = ref[i];
        int found = 0;
        for (int j=0;j<frames;j++) if (frame[j] == page) { found = 1; break; }
        if (!found) {
            frame[front] = page;
            front = (front + 1) % frames;
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
