#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>



int main()
{
	char *buf1;
	int fd,ret;
	ssize_t bytesrd;
	
	while(1){
	fd = open("fifo",O_RDONLY);
	if(fd < 0){
		perror("File open error\n");
		return 1;
	}
	buf1 = (char*)malloc(2048*sizeof(char));
	if(buf1 == NULL){
		perror("Memory allocation error\n");
	}

	bytesrd = read(fd, buf1 ,2048);
	if(bytesrd < 0){
		perror("read error\n");
		return 1;
	}
	printf("%s",buf1);
	
	close(fd);
	}
	return 0;

}
