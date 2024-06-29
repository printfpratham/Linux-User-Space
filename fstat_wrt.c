#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd,fd1;
	long int bufsize;
	ssize_t bytesrd,byteswrt;
	char *buf;
	struct stat st;


	fd = open("hii.txt",O_RDONLY);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);


	fd1 = open("hello.txt",O_CREAT|O_RDWR,S_IRWXU);
	printf("fd1: %d\n",fd1);
	int ret = fstat(fd,&st);
	if(ret != 0){
		perror("stat error\n");
		return 1;
	}

	printf("size is: %ld,block size: %ld\n",st.st_size,st.st_blksize);
	
	buf = (char*)malloc(st.st_size*sizeof(char));
		
	bytesrd = read(fd,buf,st.st_size);
	printf("bytes read: %ld\n",bytesrd);
	
	byteswrt = write(fd1,buf,bytesrd);
	printf("bytes write: %ld\n",byteswrt);
	//bufsize = bytesrd;
	
	printf("%s",buf);
	close(fd);
	close(fd1);
	free(buf);
	return 0;
}





