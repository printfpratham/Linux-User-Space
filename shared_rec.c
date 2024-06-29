#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


int main()
{
	key_t key;
	int ret,shm_id;
	int count = 0;
	char* str;
	//str = (char*)malloc(2048*sizeof(char));
	key = ftok("shm_file",7);
	if(key < 0){
		perror("Key generation error\n");
		return 1;
	}
	else{
		printf("Key Generated: %d\n",key);
	}
	shm_id = shmget(key,1024,0666|IPC_CREAT);
	if(shm_id < 0){
		perror("Shared memory allocation error\n");
		return 1;
	}
	str = (char*)shmat(shm_id,(void*)0,0);
	if(str == NULL){
		perror("ATTCHMENT ERROR\n");
		return 1;
	}
		
	fputs(str,stdout);
	

	shmdt(str);
	ret = shmctl(shm_id, IPC_RMID, NULL);
	if(ret == 0){
		printf("MEMORY DESTROY SUCCESSS\n");
	}
	else{
		printf("MEMORY DID NOT DESTROYED\n");
	}
	return 0;

}
