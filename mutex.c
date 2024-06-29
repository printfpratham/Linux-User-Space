#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0; 
pthread_mutex_t mut;
void *increment_counter(void *arg)
{
	int stat = pthread_mutex_lock(&mut);

    	for (int i = 0; i < 10; i++) {
        counter++;
      	sleep(1);
	printf("%ld,counter=%d\n",pthread_self(),counter);	
    	}
    	
	pthread_mutex_unlock(&mut);
    	return NULL;
}
void *increment_counter1(void *arg) {
	int stat = pthread_mutex_lock(&mut);
	if(stat != 0){
		printf("Mutex error\n");
	}

    for (int i = 0; i < 10; i++){
        counter++;
      	sleep(1);
	printf("%ld,counter=%d\n",pthread_self(),counter);	
    	}

    	pthread_mutex_unlock(&mut);
	return NULL;
}

int main() {

    pthread_t thread1, thread2;
	int ret;
   ret = pthread_mutex_init(&mut,NULL);
 	if(ret != 0){
		perror("Mutex unsuccessful\n");
		return 1;
	}


    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter1, NULL);
 
    pthread_join(thread1, NULL);
    printf("counter val: %d\n",counter);
    pthread_join(thread2, NULL);
//    printf("Thread 1 val: %d\n",counter);
 
    printf("Final counter value: %d\n", counter);
	pthread_mutex_destroy(&sema); 
    return 0;
}
