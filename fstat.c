#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd;
	long int bufsize;
	ssize_t bytesrd;
	char *buf;
	struct stat st;
	fd = open("hii.txt",O_RDONLY);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);
	int ret = fstat(fd,&st);
	if(ret != 0){
		perror("stat error\n");
		return 1;
	}
	printf("size is: %ld,block size: %ld\n",st.st_size,st.st_blksize);
	buf = (char*)malloc(st.st_size*sizeof(char));
		
	bytesrd = read(fd,buf,st.st_size);
	printf("bytes read: %ld\n",bytesrd);
	//bufsize = bytesrd;
	
	printf("%s",buf);
	close(fd);
	free(buf);
	return 0;
}





