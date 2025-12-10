#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Block {
    int blockNumber;
    struct Block *next;
};

struct Block* createBlock(int blockNumber) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->blockNumber = blockNumber;
    newBlock->next = NULL;
    return newBlock;
}


void addBlock(struct Block **head, int blockNumber) {
    struct Block* newBlock = createBlock(blockNumber);
    if (*head == NULL) {
        *head = newBlock;
    } else {
        struct Block* temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newBlock;
    }
}

void displayFile(struct Block *head) {
    struct Block *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->blockNumber);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int n, i, block;
    struct Block* file = NULL;

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    printf("Enter block numbers for the file:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &block);
        addBlock(&file, block);
    }

    printf("\nLinked Allocation of File:\n");
    displayFile(file);

    return 0;
}

