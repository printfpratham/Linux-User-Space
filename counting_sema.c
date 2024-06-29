#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
 
#define NUM_RESOURCES 5 // Number of available resources
 
sem_t resource_semaphore;
 
void* use_resource(void* arg) {
    int resource_id = *((int*)arg);
    sem_wait(&resource_semaphore); // Wait for available resource
    printf("Thread %ld is using resource %d.\n", pthread_self(), resource_id);
    // Simulate resource usage time
    sleep(2);
    sem_post(&resource_semaphore); // Release resource
    printf("Thread %ld released resource %d.\n", pthread_self(), resource_id);
    return NULL;
}
 
int main() {
    pthread_t threads[5];
 
    sem_init(&resource_semaphore, 0, NUM_RESOURCES);
 
    int resource_ids[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        resource_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, use_resource, &resource_ids[i]);
    }
 
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        pthread_join(threads[i], NULL);
    }
 
    sem_destroy(&resource_semaphore);
 
    return 0;
}

