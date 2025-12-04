#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid, at, bt, pr, rt;
} Process;

int main() {
    Process p[] = {{1,0,7,2,7},{2,2,4,1,4},{3,4,1,3,1}};
    int n = 3, time = 0, completed = 0, min_pr, idx;

    printf("Gantt Chart: ");

    while(completed != n){
        min_pr = 999;
        idx = -1;

        for(int i=0;i<n;i++){
            if(p[i].at <= time && p[i].rt > 0 && p[i].pr < min_pr){
                min_pr = p[i].pr;
                idx = i;
            }
        }

        if(idx != -1){
            printf("P%d ", p[idx].pid);
            p[idx].rt--;
            if(p[idx].rt == 0)
                completed++;
        }

        time++;
    }

    printf("\n");
    system("pause");
    return 0;
}
