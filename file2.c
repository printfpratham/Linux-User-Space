#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd,fd1;
	ssize_t bytesrd,byteswrt;
	char buf[2048]= {0};
	
	fd = open("/proc/version_signature",O_RDONLY);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	fd1 = open("hii.txt",O_CREAT|O_RDWR|O_APPEND,S_IRUSR|S_IWUSR);
	if(fd1<0){
		perror("File opening error\n");
		return 1;
	}
	printf("fd: %d fd1: %d\n",fd,fd1);
	bytesrd = read(fd,buf,2048);

	if(bytesrd < 0){
		perror("error reading\n");
		return -1;
	}


	byteswrt = write(fd1,buf,bytesrd);

	if(byteswrt < 0){
		perror("error writing\n");
		return -2;
	}

	printf("bytes read: %ld\n",bytesrd);
	printf("bytes write: %ld\n",byteswrt);
	printf("%s\n",buf);
	close(fd);
	close(fd1);
	return 0;
}





