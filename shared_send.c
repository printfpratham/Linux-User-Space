#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>


int main()
{
	key_t key;
	int ret,shm_id;
	char* str;
	int count = 0;


	key = ftok("shm_file",7);
	if(key < 0){
		perror("Key generation error\n");
		return 1;
	}
	else{
		printf("Key generated: %d\n",key);
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
	printf("Enter the string\n");

	fgets(str,100,stdin);
	printf("Data written\n");
	//shmdt(str);
	return 0;

}
