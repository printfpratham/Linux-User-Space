#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd,fd1;
	ssize_t bytesrd,byteswrt;
	char buf[1024]= "HELLO";
	char buf1[1024] = {0};
	fd = open("hello.txt",O_CREAT|O_WRONLY|O_APPEND);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);
	byteswrt = write(fd,buf,strlen(buf));
	printf("bytes write: %ld\n",byteswrt);
	system("ls -l hello.txt");
//	bytesrd = read(fd,buf1,byteswrt);
	system("ls -l hello.txt");
	printf("bytes read: %ld\n",bytesrd);
	system("ls -l hello.txt");
	printf("%s",buf1);
	system("ls -l hello.txt");
	close(fd);


	fd1 = open("hello.txt",O_RDONLY);
	printf("fd1: %d\n",fd1);
	bytesrd = read(fd1,buf1,byteswrt);
	printf("bytes read: %ld\n",bytesrd);
	printf("%s",buf1);
	close(fd1);
	return 0;
}





