#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/select.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 100

struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAX];
} message;


void *read(void *p)
{
	
	key_t key;
	key = ftok("key1", 22);
	int msgid1;

	msgid1 = msgget(key, 0666 | IPC_CREAT);

	while(1){

	msgrcv(msgid1, &message, sizeof(message), 2, 0);

	printf("Received : %s \n", message.mesg_text);

	}

}

void *write(void *p)
{

	key_t key;
	key = ftok("key1", 22);
	int msgid;


	msgid = msgget(key+1, 0666 | IPC_CREAT);
	while(1){
	message.mesg_type = 1;

	fgets(message.mesg_text, MAX, stdin);

	msgsnd(msgid, &message, sizeof(message), 0);

	}
}

int main()
{

	pthread_t id1,id2;
	int err;
	
	err=pthread_create(&id1, NULL,read,NULL);
	if(err!=0)
	{
        	printf("thread not created\n");
       		exit(0);
	}

	
	err=pthread_create(&id2, NULL,write,NULL);
	if(err!=0)
	{
        	printf("thread not created\n");
       		exit(0);
	}

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);

	exit(0);

}
