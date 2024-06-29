#include <stdio.h>
#include <pthread.h>


//int i =
void *thread(void* p)
{
	printf("Value received in thread 1:%d\n",*(int *)p);
	return p;
}

void *thread1(void* p)
{
	printf("Value received in thread 2: %d\n",*(int *)p);
	return p;

}
int main()
{
	pthread_t tid,tid1;
	int j = 1,k = 2,ret;
	ret = pthread_create(&tid,NULL,thread,&j);
	ret = pthread_create(&tid1,NULL,thread1,&k);
	void *ptr;
	void *ptr1;
	pthread_join(tid,&ptr);
	pthread_join(tid1, &ptr1);
	printf("value received from thread-1: %d\n",*(int *)ptr);
	printf("value received from thread-2: %d\n",*(int *)ptr1);

}
