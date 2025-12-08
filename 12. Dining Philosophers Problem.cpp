#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];

void* philosopher(void* num) {
    int id = *(int*)num;

    printf("Philosopher %d is thinking\n", id);
    sleep(1);

    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d is eating\n", id);
    sleep(1);

    sem_post(&chopstick[id]);
    sem_post(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d finished eating\n", id);

    return NULL;
}

int main() {
    pthread_t t[5];
    int i, id[5];

    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for (i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(t[i], NULL);

    return 0;
}
