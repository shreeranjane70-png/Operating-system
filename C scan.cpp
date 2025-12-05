#include <stdio.h>
#include <stdlib.h>

int main() {
    int req[100], n, head, disk_size, total = 0;
    int i, j, temp;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (max cylinder): ");
    scanf("%d", &disk_size);

    // Add head and boundaries for circular scanning
    req[n] = head;
    req[n + 1] = 0;
    req[n + 2] = disk_size - 1;
    n += 3;

    // Sort requests
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find index of head
    int head_index;
    for (i = 0; i < n; i++) {
        if (req[i] == head) {
            head_index = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling Order:\n");

    // Move to right first
    for (i = head_index; i < n; i++)
        printf("%d ", req[i]);

    // Wrap around to start of disk
    for (i = 0; i < head_index; i++)
        printf("%d ", req[i]);

    // Calculate total head movement
    total += abs(head - (disk_size - 1));   // move to end
    total += disk_size - 1;                 // wrap back to 0
    total += abs(req[1] - 0);               // continue from 0

    printf("\nTotal head movement = %d cylinders\n", total);

    return 0;
}
