#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <semaphore.h>

pthread_mutex_t mut;
struct stat st;
sem_t sema;



void* write_thread(void *p)
{
	char *buf = "Hello Silicon Signal\n";
	
	int fd;
	ssize_t byteswrt;
	pthread_mutex_lock(&mut);
	fd = open("assignment.txt",O_CREAT|O_RDWR|O_APPEND,0666);
	if(fd < 0){
		perror("File openning error\n");
		exit(1);		
	}

	byteswrt = write(fd,buf,strlen(buf));
	if(byteswrt > 0){
		printf("Number of bytes written %ld\n",byteswrt);
	}
	pthread_mutex_unlock(&mut);
	close(fd);
	return NULL;
}

void* read_thread(void *p)
{
	char* buf1;
	int fd1,count;
	ssize_t bytesrd;
	
	pthread_mutex_lock(&mut);
	fd1 = open("assignment.txt",O_RDWR);
	if(fd1 < 0){
		perror("File opening error\n");
		
	}
	int ret = fstat(fd1,&st);
	if(ret != 0){
		perror("Fstate error\n");
		
	}
	else{
		printf("file size is %ld\n",st.st_size);
	}

	buf1 = (char*)malloc(st.st_size*sizeof(char));
	if(buf1 == NULL){
		perror("Memory allocation error\n");
		exit(1);
	}

	bytesrd = read(fd1,buf1,st.st_size);
	if(bytesrd > 0){
		printf("%s\n",buf1);
	}
	else{
		perror("read error\n");
		exit(1);
	}

	pthread_mutex_unlock(&mut);
	close(fd1);
	
	char *s;
	char str[100];
	int index;
	while((s = strstr(buf1+index ,"Silicon Signal")) != NULL){
		index = (s - buf1) + 1;
		count++;

		
	}
	printf("%d\n",count);
	sprintf(str, "Count = %d\n",count);

	pthread_mutex_lock(&mut);
	int fd2 = open("count.txt",O_CREAT|O_RDWR,0666);
	if(fd2 < 0){
		perror("File open error\n");
		exit(1);
	}
	ret = write(fd2,str,strlen(str));
	if(ret < 0){
		perror("Write error\n");
		exit(1);
	}
	close(fd2);
	pthread_mutex_unlock(&mut);

	free(buf1);
	
	return NULL;
}


int main()
{
	pthread_t w_thread, r_thread;
	int ret;

	ret = pthread_mutex_init(&mut,NULL);
	if(ret != 0){
		perror("Mutex init error\n");
	}

	ret = pthread_create(&w_thread,NULL,write_thread,NULL);
	if(ret != 0){
		perror("Thread creation error\n");
		return 1;
	}

	ret = pthread_create(&r_thread,NULL,read_thread,NULL);
	if(ret != 0){
		perror("Thread creation error\n");
		return 1;
	}


	ret = pthread_join(w_thread,NULL);
	if(ret != 0){
		perror("Thread termination error\n");
		return 1;
	}

	ret = pthread_join(r_thread,NULL);
	if(ret != 0){
		perror("Thread termination error\n");
		return 1;
	}

	ret = pthread_mutex_destroy(&mut);
	if(ret != 0){
		perror("Mutex destroy error\n");
		return 1;
	}

	return 0;
}


	

