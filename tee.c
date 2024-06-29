#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#define _GNU_SOURCE

int main(int argc,char* argv[])
{
	int fd;
	size_t len,slen;
	
	fd = open(argv[1],O_CREAT|O_WRONLY|O_TRUNC,0644);
	if(fd<0){
		perror("File open error\n");
		return 1;
	}
	printf("fd: %d\n",fd);
	if(bytesrd < 0){
		perror("file read error\n");
		return 2;
	}

	len = tee(0,1,INT_MAX,0);
	printf("%ld bytes were duplicated\n",len);


	if(len > 0){
		slen = splice(STDIN_FILENO,NULL,fd,NULL,len,0);
		if(slen < 0){
			perror("splice error\n");
			return 1;
		}
		else{
			printf("Spliced content: %d\n",slen);
		}
	}

	close(fd);
	return 0;
}





