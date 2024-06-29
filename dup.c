#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int fd,fd1,fd2;
	ssize_t byteswrt_fd,byteswrt_fd1;
	char buf[] = "hello writing from fd\n";
	char buf1[] = "hello writing from fd1\n";
	
	fd = open("hii.txt",O_RDWR);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);
	byteswrt_fd = write(fd,buf,strlen(buf));
	printf("bytes written from fd is: %ld\n",byteswrt_fd);
	fd1 = dup(fd);

	
	if(fd1<0){
		perror("file duplication error\n");
		return 1;
	}

	printf("New file descriptor is %d\n",fd1);

	byteswrt_fd1 = write(fd1,buf1,strlen(buf1));
	
	printf("bytes written from fd1 is: %ld\n",byteswrt_fd1);
	
	close(fd);
	close(fd1);
	system("cat hii.txt");
	return 0;
}





