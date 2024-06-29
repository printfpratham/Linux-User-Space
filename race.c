#include <stdio.h>
#include <pthread.h>
 
int counter = 0;  
 
void *increment_counter(void *arg) {
	
    for (int i = 0; i < 10; i++) {
        counter++;
	printf("%ld,counter=%d\n",pthread_self(),counter);	
    }
    return NULL;
}
 
int main() {
    pthread_t thread1, thread2;
 
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);
 
    pthread_join(thread1, NULL);
    printf("counter val: %d\n",counter);
    pthread_join(thread2, NULL);
 
    printf("Final counter value: %d\n", counter);
 
    return 0;
}
