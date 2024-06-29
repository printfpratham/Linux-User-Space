#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/udp.h>

int main()
{
	ssize_t bytes_sent,bytes_rec;
	struct sockaddr_in servaddr,cliaddr;
	int fd,ret,data;
	fd_set rset;

	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd < 0){
		perror("Socket creation error\n");
		return 1;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5000);
	servaddr.sin_addr.s_addr = inet_addr("192.168.200.187");
	socklen_t setup_len = sizeof(servaddr);

	ret = connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(ret < 0){
		perror("Connect failed\n");
		return 1;
	}


	while(1){

		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(fd,&rset);

		char *buffer = (char*)malloc(1024*sizeof(char));

		select(fd+1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(0,&rset)){
			printf("Enter Message: \n");
			fgets(buffer,100,stdin);
			ret = sendto(fd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr*)NULL,sizeof(servaddr));
			buffer[ret] = '\0';
			memset(buffer,0,strlen(buffer));
		}

		char* msg = (char*)malloc(1024*sizeof(char));
		if(FD_ISSET(fd,&rset)){
			ret = recvfrom(fd,msg,sizeof(msg),MSG_WAITALL,(struct sockaddr*)NULL,NULL);
			msg[ret] = '\0';
			printf("Server: %s\n",msg);
		}
		memset(msg,0,strlen(msg));
		free(buffer);
		free(msg);
	}
	return 0;
}
