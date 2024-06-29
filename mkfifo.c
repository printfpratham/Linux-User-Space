#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>



int main()
{
	char *buf;
	int fd,ret;
	ssize_t bytesrd, byteswrt;
	
	ret = mkfifo("fifo",0666);
	if(ret != 0){
		perror("Fifo error\n");
	}
	while(1){
	fd = open("fifo",O_WRONLY);
	if(fd < 0){
		perror("File open error\n");
		return 1;
	}

	buf = (char*)malloc(2048*sizeof(char));
	fgets(buf, 2048, stdin);
	byteswrt = write(fd, buf ,2048);
	if(byteswrt < 0){
		perror("write error\n");
		return 1;
	}
	
	
	close(fd);
	}
	return 0;

}
