// producer_consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUF_SIZE 5
int buffer[BUF_SIZE];
int in = 0, out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg){
    int id = *(int*)arg;
    for(int i=0;i<5;i++){
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = i + id*100;
        printf("Producer %d produced %d at %d\n", id, buffer[in], in);
        in = (in+1)%BUF_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg){
    int id = *(int*)arg;
    for(int i=0;i<5;i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int val = buffer[out];
        printf("Consumer %d consumed %d from %d\n", id, val, out);
        out = (out+1)%BUF_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main(){
    sem_init(&empty,0,BUF_SIZE);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_t p,c;
    int pid=1, cid=1;
    pthread_create(&p,NULL,producer,&pid);
    pthread_create(&c,NULL,consumer,&cid);
    pthread_join(p,NULL);
    pthread_join(c,NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
