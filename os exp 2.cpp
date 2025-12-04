#include <stdio.h>

struct Process {
    int pid;            
    int burstTime;      
    int priority;       
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for process %d\n", i + 1);

        p[i].pid = i + 1;

        printf("Burst Time: ");
        scanf("%d", &p[i].burstTime);

        printf("Priority: ");
        scanf("%d", &p[i].priority);
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    
    int waitingTime[n], turnaroundTime[n];
    waitingTime[0] = 0; 

    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + p[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + p[i].burstTime;
    }

    
    printf("\n--- Priority Scheduling Result ---\n");
    printf("PID\tBurst\tPriority\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].burstTime, p[i].pri

