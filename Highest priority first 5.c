#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int priority;
    int wt;
    int tat;
};

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time and Priority for P%d: ", i+1);
        scanf("%d %d", &p[i].bt, &p[i].priority);
    }

    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-i-1; j++) {
            if(p[j].priority < p[j+1].priority) { 
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

  
    p[0].wt = 0;
    for(i = 1; i < n; i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;

  
    for(i = 0; i < n; i++)
        p[i].tat = p[i].wt + p[i].bt;

   
    printf("\nPID\tBT\tPR\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].bt, p[i].priority, p[i].wt, p[i].tat);

    return 0;
}

