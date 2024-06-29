#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0; 
sem_t sema;
void *increment_counter(void *arg)
{
	sem_wait(&sema);

    	for (int i = 0; i < 10; i++) {
        counter++;
      	sleep(1);
	printf("%ld,counter=%d\n",pthread_self(),counter);	
    	}
    	
	sem_post(&sema);
    	return NULL;
}

int main() {

    pthread_t thread1, thread2;
	int ret;
   ret = sem_init(&sema,0,1);
 	if(ret != 0){
		perror("Semaphore unsuccessful\n");
		return 1;
	}


 	ret =  pthread_create(&thread1, NULL, increment_counter, NULL);
 	if(ret != 0)
		perror("Thread creation error\n");
    	ret = pthread_create(&thread2, NULL, increment_counter, NULL);
 	if(ret != 0)
		perror("Thread creation error\n");
 
    	pthread_join(thread1, NULL);
    	printf("counter val after thread-1: %d\n",counter);
    	pthread_join(thread2, NULL);
//    printf("Thread 1 val: %d\n",counter);
 
    	printf("Final counter value: %d\n", counter);
	sem_destroy(&sema); 
    	return 0;
}
