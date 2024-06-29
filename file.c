#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int fd,fd1;
	ssize_t bytesrd;
	char buf[1024];
	fd = open("/proc/version_signature",O_RDONLY);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);
	bytesrd = read(fd,buf,sizeof(buf));
	printf("bytes read: %ld\n",bytesrd);
	printf("%s\n",buf);
	close(fd1);
	return 0;
}





