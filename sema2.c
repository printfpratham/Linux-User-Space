#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int i,ret;
int *ptr  = &ret;
sem_t sema;
void *thread(void* p)
{
	ret = sem_wait(&sema);
	if(ret != 0)
		perror("semaphore lock unsucess\n");
	sem_getvalue(&sema,ptr);
	printf("Thread id: %ld,Semaphore Value: %d\n",pthread_self(),*ptr);
	printf("Enter value of i\n");
	scanf("%d",&i);

	sem_post(&sema);
	sem_getvalue(&sema,ptr);
	printf("Thread id: %ld,Semaphore Value: %d\n",pthread_self(),*ptr);
	return NULL;
		
}
void *thread1(void* p)
{
	//sleep(3);
	
	sem_getvalue(&sema,ptr);
	printf("Thread id: %ld,Semaphore Value: %d\n",pthread_self(),*ptr);
	ret = sem_wait(&sema);
	if(ret != 0)
		perror("semaphore lock unsucess\n");
	//printf("Thread id: %ld\n",pthread_self());
	printf("Value of i is %d\n",i);
	sem_getvalue(&sema,ptr);
	printf("Thread id: %ld,Semaphore Value: %d\n",pthread_self(),*ptr);
	sem_post(&sema);
	sem_getvalue(&sema,ptr);
	printf("Thread id: %ld,Semaphore Value: %d\n",pthread_self(),*ptr);
	return NULL;
}
int main()
{
	pthread_t tid,tid1;
	int j = 1,k = 2;
	ret = sem_init(&sema,0,1);
	if(ret != 0)
		printf("Semaphore initializatin failure\n");

		
	
		ret = pthread_create(&tid,NULL,thread,&j);
		if(ret != 0)
			printf("Thread creation error\n");

		ret = pthread_create(&tid1,NULL,thread1,&k);
		if(ret != 0)
			printf("Thread creation error\n");


		pthread_join(tid,NULL);
		pthread_join(tid1,NULL);
	
	sem_destroy(&sema);
	
	
	

}
