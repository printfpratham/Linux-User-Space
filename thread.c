#include <stdio.h>
#include <pthread.h>

void* thread()
{
	sleep(1);
	printf("Inside of thread with Thread id: %d\n",pthread_self());
	
}


int main()
{
	pthread_t t_id;
	
	int ret;
	ret= pthread_create(&t_id, NULL ,thread,NULL);
	if(ret == 0)
		printf("Thread created\n");
	pthread_join(t_id, NULL);
	printf("Exit from thread\n");

	

}










