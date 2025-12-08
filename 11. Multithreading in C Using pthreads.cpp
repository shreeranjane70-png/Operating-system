#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Thread function
void* threadFunction(void* arg) {
    char msg[100];
    
    // Copy argument safely
    strcpy(msg, (char*)arg);

    printf("%s\n", msg);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Messages stored in arrays (safe)
    char msg1[] = "Hello from Thread 1";
    char msg2[] = "Hello from Thread 2";

    // Create threads
    pthread_create(&t1, NULL, threadFunction, (void*)msg1);
    pthread_create(&t2, NULL, threadFunction, (void*)msg2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
