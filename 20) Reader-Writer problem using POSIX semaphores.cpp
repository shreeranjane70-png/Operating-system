// reader_writer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;
int readcount = 0;
sem_t mutex;     // protect readcount
sem_t wrt;       // writers lock

void *reader(void *arg){
    int id = *(int*)arg;
    while(1){
        sem_wait(&mutex);
        readcount++;
        if(readcount==1) sem_wait(&wrt);
        sem_post(&mutex);

        // reading
        printf("Reader %d: read data = %d\n", id, data);
        sleep(1);

        sem_wait(&mutex);
        readcount--;
        if(readcount==0) sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
        break; // single iteration for demo
    }
    return NULL;
}

void *writer(void *arg){
    int id = *(int*)arg;
    while(1){
        sem_wait(&wrt);
        data += 10;
        printf("Writer %d: wrote data = %d\n", id, data);
        sleep(1);
        sem_post(&wrt);
        sleep(1);
        break; // single iteration for demo
    }
    return NULL;
}

int main(){
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    pthread_t r1,r2,w1;
    int id1=1,id2=2,id3=1;
    pthread_create(&r1,NULL,reader,&id1);
    pthread_create(&w1,NULL,writer,&id3);
    pthread_create(&r2,NULL,reader,&id2);

    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(w1,NULL);

    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}
