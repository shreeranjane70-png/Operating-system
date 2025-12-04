#include <stdio.h>

struct Process {
    int pid;
    int burst;
    int waiting;
    int turnaround;
};

void sortByBurst(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[j].burst < p[i].burst) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].burst);
    }

    
    sortByBurst(p, n);

    
    p[0].waiting = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting = p[i - 1].waiting + p[i - 1].burst;
    }

    for (int i = 0; i < n; i++) {
        p[i].turnaround = p[i].waiting + p[i].burst;
    }

    
    printf("\nSJF Scheduling Results:\n");
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    
    float avg_wait = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wait += p[i].waiting;
        avg_tat += p[i].turnaround;
    }

    printf("\nAverage waiting time: %.2f", avg_wait / n);
    printf("\nAverage turnaround time: %.2f\n", avg_tat / n);

    return 0;
}

