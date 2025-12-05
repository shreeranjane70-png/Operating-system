// linked_allocation.c
// Simulates linked allocation: each block contains pointer to next block.
// Directory keeps pointer to first and last.

#include <stdio.h>

int main() {
    int total_blocks;
    printf("Enter total disk blocks available: ");
    scanf("%d",&total_blocks);

    int file_blocks;
    printf("Enter number of blocks for the file: ");
    scanf("%d",&file_blocks);

    int blocks[file_blocks];
    printf("Enter block numbers in chain order (first to last):\n");
    for(int i=0;i<file_blocks;i++) scanf("%d",&blocks[i]);

    printf("\nDirectory points to first block %d and last block %d.\n", blocks[0], blocks[file_blocks-1]);
    printf("Block chain (block -> next):\n");
    for(int i=0;i<file_blocks;i++){
        if(i < file_blocks-1) printf("%d -> %d\n", blocks[i], blocks[i+1]);
        else printf("%d -> NULL (end)\n", blocks[i]);
    }

    int access_k;
    printf("Enter kth block to access (0-based within file): ");
    scanf("%d",&access_k);
    if(access_k <0 || access_k >= file_blocks){ printf("Invalid index.\n"); return 0; }

    printf("To access record at index %d, follow pointers starting from block %d:\n", access_k, blocks[0]);
    for(int i=0;i<=access_k;i++){
        if(i>0) printf(" -> ");
        printf("%d", blocks[i]);
    }
    printf("\n(You read %d blocks while following the chain.)\n", access_k+1);
    return 0;
}
