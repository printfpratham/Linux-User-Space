#include <stdio.h>
#include <pthread.h>


int i=2;
void *thread(void* p)
{
	printf("Value received %s\n",((char*)p));
	//int a = 5;
//	p = (void*)5; 
	char* p1 = "world";
	return (void*)p1;
}
int main()
{
	pthread_t tid;
	int ret, j = 1;

	ret = pthread_create(&tid,NULL,thread,"Hello");
	if(ret != 0)
	{
		printf("Thread unsuccessful\n");
	}

	void* ptr=NULL;
	pthread_join(tid,&ptr);
	printf("value returned by thread: %s\n",(char*)ptr);

}
