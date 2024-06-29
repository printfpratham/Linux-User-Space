#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t empty,full,sm;
//int full = 0;
//int empty = 10;
int data = 0;

void* producer(void *p)
{
	int produced;
	printf("\nProducer created with thread id: %ld\n",pthread_self());
	for(produced = 0;produced<50;produced++)
	{
		sem_wait(&empty);
		sem_wait(&sm);

		data=produced;

		sem_post(&sm);

	
	printf("\nProducer produces item no: %d\n",data);

//	if(produced%5==0){
	sem_post(&full);//}
	sleep(1);
	}
	//sem_post(&sema);
	return NULL;
}
void* consumer(void *p)
{
	int consumed,total=0;
	printf("Consumer started with thread id: %ld\n",pthread_self());

	for(consumed=0; consumed<50; consumed++)
	{
	sem_wait(&full);

		sem_wait(&sm);
		total = total+data;
		sem_post(&sm);

	sem_post(&empty);
	printf("Consumer consumes item no: %d\n",data);
	}
	printf("\nTotal consumed : %d\n",total);
	//data--;
	//sem_post(&sema);
	return NULL;

}



int main()
{
	pthread_t thread1, thread2;
	int stat = sem_init(&empty,1,1);
	 stat = sem_init(&full,1,0);
	 stat = sem_init(&sm,1,1);

	if(stat != 0){
		perror("Semaphore init error\n");
		return 1;
	}
	pthread_create(&thread1,NULL,producer,NULL);
	pthread_create(&thread2,NULL,consumer,NULL);


	pthread_join(thread1,NULL);
	printf("Producer finished\n");

	pthread_join(thread2,NULL);
	

	return 0;

}
