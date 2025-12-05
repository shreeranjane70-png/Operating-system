// indexed_allocation.c
// Simulates indexed allocation where an index block holds pointers to file blocks.

#include <stdio.h>

int main() {
    int total_blocks;
    printf("Enter total disk blocks available: ");
    scanf("%d",&total_blocks);

    int file_blocks;
    printf("Enter number of blocks required by file: ");
    scanf("%d",&file_blocks);

    int index_block;
    printf("Choose an index block (0..%d): ", total_blocks-1);
    scanf("%d",&index_block);

    if(index_block < 0 || index_block >= total_blocks){
        printf("Invalid index block.\n"); return 0;
    }

    int blocks[file_blocks];
    printf("Enter block numbers for each file block (space separated):\n");
    for(int i=0;i<file_blocks;i++) scanf("%d",&blocks[i]);

    printf("\nIndex block %d contains pointers to:\n", index_block);
    for(int i=0;i<file_blocks;i++){
        printf("Entry %d -> Block %d\n", i, blocks[i]);
    }

    int access_idx;
    printf("Enter file block number to access (0-based index within file): ");
    scanf("%d",&access_idx);
    if(access_idx < 0 || access_idx >= file_blocks){ printf("Invalid index.\n"); return 0; }

    printf("To access file block %d, read index block %d then data block %d.\n",
           access_idx, index_block, blocks[access_idx]);
    return 0;
}
