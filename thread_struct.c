#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
struct pratham {
	int id;
	char name[10];
};


void *thread(void* p)
{
	
	struct pratham *pt = (struct pratham*)p;
	pt -> id = 29;
	//pt -> name
	strcpy((pt-> name),"hello");
	//((struct pratham *)p) -> id = 29;
	//strcpy(((struct pratham *)p)-> name,"hello");
	return (void*)pt;
}
int main()
{
	pthread_t tid;
	int ret, j = 1;
	struct pratham *p1 = (struct pratham *)malloc(sizeof(struct pratham));

	ret = pthread_create(&tid,NULL,thread,p1);
	if(ret != 0)
	{
		printf("Thread unsuccessful\n");
	}

	void* ptr=NULL;
	pthread_join(tid,&ptr);
	
	printf("value returned by thread: %d ,%s\n",((struct pratham *)ptr)->id,((struct pratham *)ptr)->name);

}
