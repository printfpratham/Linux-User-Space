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
	struct msgbuf msg,rmsg;
	struct msqid_ds info;
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

	while(1){
	ret = msgrcv(msq_id,&rmsg,sizeof(rmsg),1,0);
		
	if(ret > 0){
		printf("Message Received: ");
		fputs(rmsg.m_data,stdout);
	}
	memset(rmsg.m_data,0,strlen(rmsg.m_data));	


	printf("Enter Message: \n");
	msg.m_type = 2;
	fgets(msg.m_data,100,stdin);
	ret = msgsnd(msq_id,&msg,strlen(msg.m_data),0);
	
	memset(msg.m_data,0,strlen(msg.m_data));	
	
	}

	

	ret  = msgctl(msq_id,IPC_STAT,&info);
	if(info.msg_qnum == 0){
		ret = msgctl(msq_id,IPC_RMID,0);
		if(ret == 0){
			printf("MESSAGE QUEUE DESTRYED\n");
		}
	}
	
	return 0;
}
