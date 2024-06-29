#include <stdio.h>
#include <pthread.h>


int i=2;
void *thread(void* p)
{
	printf("Value received %d\n",(*(int*)p));
	int a = 5;
//	p = (void*)5; 

	*(int*)p = a;
	return p;
}
int main()
{
	pthread_t tid;
	int ret, j = 1;

	ret = pthread_create(&tid,NULL,thread,&j);
	if(ret != 0)
	{
		printf("Thread unsuccessful\n");
	}

	void* ptr=NULL;
	pthread_join(tid,&ptr);
	printf("value returned by thread: %d\n",*(int*)ptr);

}
