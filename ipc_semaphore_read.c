#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};




int main()
{
	char str[100];
	key_t key;
	int sem_id,fd,ret;
	struct sembuf sem;
	union semun semval;
	ssize_t bytesrd;

	key = ftok("semaphore_ipc",5);
	if(key < 0){
		perror("Key generation error\n");
		return 1;
	}
	semval.val = 0;
	sem_id = semget(key,1,0666|IPC_CREAT);
	if(sem_id < 0){
		perror("Semaphore generation error\n");
		return 1;
	}
	//semval.val = 1;
	
	ret = semctl(sem_id,0,SETVAL,semval);
	if(ret < 0){
		perror("Semaphore ctl error\n");
		return 1;
	}

	fd = open("test.txt",O_RDONLY);
	if(fd < 0){
		perror("File open error\n");
		return 1;
	}

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;

	ret = semop(sem_id,&sem,1);
	if(ret < 0){
		perror("Semaphore operation error\n");
		return 1;
	}

	bytesrd = read(fd,str,50);
	fputs(str,stdout);
	if(bytesrd < 0){
		perror("read error\n");
		return 1;
	}
	else{
		printf("Bytes read : %ld\n",bytesrd);
	}
	sem.sem_op = 1;
	sem.sem_flg = 0;
	ret = semop(sem_id,&sem,1);
	if(ret < 0){
		perror("Semaphore operation error-2\n");
		return 1;
	}

	close(fd);


	ret = semctl(sem_id,0,IPC_RMID);
	if(ret == 0){
		printf("SEMAPHORE DESTROY SUCCESS\n");
	}

	return 0;
}






		
	


