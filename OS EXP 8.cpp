#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid, bt, wt, tat;
} Process;

int main() {
    Process p[] = {{1,6,0,0},{2,8,0,0},{3,7,0,0},{4,3,0,0}};
    int n = 4;

    // Sort by burst time
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(p[i].bt > p[j].bt){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    p[0].wt = 0;
    for(int i=1;i<n;i++)
        p[i].wt = p[i-1].wt + p[i-1].bt;

    for(int i=0;i<n;i++)
        p[i].tat = p[i].wt + p[i].bt;

    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);

    system("pause");
    return 0;
}
