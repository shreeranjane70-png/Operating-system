// thread_equal.c
#include <stdio.h>
#include <pthread.h>

void *worker(void *arg){
    pthread_t self = pthread_self();
    printf("Thread started\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t t;
    pthread_create(&t,NULL,worker,NULL);
    pthread_t main_id = pthread_self();
    if(pthread_equal(t, main_id))
        printf("Threads equal\n");
    else
        printf("Threads NOT equal\n");
    pthread_join(t,NULL);
    return 0;
}
