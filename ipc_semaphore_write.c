#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
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
	ssize_t byteswrt;

	key = ftok("semaphore_ipc",5);
	if(key < 0){
		perror("Key generation error\n");
		return 1;
	}

	sem_id = semget(key,1,0666|IPC_CREAT);
	if(sem_id < 0){
		perror("Semaphore generation error\n");
		return 1;
	}
	semval.val = 1;
	
	ret = semctl(sem_id,0,SETVAL,semval);
	if(ret < 0){
		perror("Semaphore ctl error\n");
		return 1;
	}

	fd = open("test.txt",O_CREAT|O_RDWR|O_APPEND,0666);
	if(fd < 0){
		perror("File open error\n");
		return 1;
	}

	ret = fork();
	if(ret == 0){
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;

	ret = semop(sem_id,&sem,1);
	if(ret < 0){
		perror("Semaphore operation error\n");
		return 1;
	}
	printf("Enter the data\n");
	fgets(str,100,stdin);
	byteswrt = write(fd,str,strlen(str));
//	byteswrt = write(fd,"\n",1);
	if(byteswrt < 0){
		perror("Write error\n");
		return 1;
	}
	else{
		printf("Bytes written : %ld",byteswrt);
	}
	sem.sem_op = 1;
	sem.sem_flg = 0;
	ret = semop(sem_id,&sem,1);
	if(ret < 0){
		perror("Semaphore operation error-2\n");
		return 1;
	}
	}
	else{
		wait(NULL);
		printf("Child terminated\n");
	}

	close(fd);

//	semctl(sem_id,0,IPC_RMID);

	return 0;
}






		
	


