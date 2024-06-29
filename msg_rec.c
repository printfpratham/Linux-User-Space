#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>


struct msgbuf{
	long m_type;
	char m_data[2048];
};


int main()
{
	key_t key;
	int ret,msq_id;
	struct msgbuf msg;
	int count = 0;

	key = ftok("shm_file", 7);
	if(key < 0){
		perror("Key not generated\n");
		return 1;
	}
	else{
		printf("Key is: %x\n",key);
	}

	msq_id = msgget(key , 0666|IPC_CREAT);
	if(msq_id < 0){
		perror("Msgget error\n");
		return 1;
	}

	printf("Msg received is: \n");
	while(count < 5){
	ret = msgrcv(msq_id,&msg,sizeof(msg),0,0);
	
	if(ret > 0){
		fputs(msg.m_data,stdout);
	}
	
	count++;
	}
	
	ret  = msgctl(msq_id,IPC_RMID,0);
	if(ret == 0){
		perror("MESSAGE QUEUE DESTROYED\n");
	}
	return 0;
}
