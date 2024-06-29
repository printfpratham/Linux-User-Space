#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>


struct msgbuf{
	long m_type;
	char m_data[100];
};


int main()
{
	key_t key;
	int ret,msq_id;
	int count = 0;
	struct msgbuf msg,rmsg;

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
	
	
	while(1){

	printf("Enter your msg:\n");

	msg.m_type = 1;
	fgets(msg.m_data,100,stdin);
        	
	ret = msgsnd(msq_id,&msg,strlen(msg.m_data),0);
	if(ret < 0){
		perror("Message send error\n");
		return 1;
	}
	memset(msg.m_data,0,strlen(msg.m_data));




	ret = msgrcv(msq_id,&rmsg,sizeof(rmsg),2,0);
	if(ret > 0){
		printf("Message received:");
	}
	if(strcmp(rmsg.m_data,"exit\n") == 0){
		printf("Connection closing...\n");
			return 1;
	}
	else{
		fputs(rmsg.m_data,stdout);
	}
       	memset(rmsg.m_data,0,strlen(rmsg.m_data));	

	}
	

	return 0;
}
