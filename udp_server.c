#include "socket_inc.h"
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
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	socklen_t setup_len = sizeof(servaddr);

	ret = bind(fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if(ret < 0){
		perror("Bind error\n");
		return 1;
	}

	
while(1){	

	FD_ZERO(&rset);
	FD_SET(0,&rset);
	FD_SET(fd,&rset);	


	char *buffer = (char*)malloc(1024*sizeof(char));

	select(fd+1,&rset,NULL,NULL,NULL);

	if(FD_ISSET(fd,&rset)){
	ret = recvfrom(fd,buffer,sizeof(buffer),MSG_WAITALL,(struct sockaddr*)&cliaddr,&setup_len);
		buffer[ret] = '\0';
	printf("Client: %s\n",buffer);
	memset(buffer,0,sizeof(buffer));
	}

	if(FD_ISSET(0,&rset)){
	fgets(buffer,200,stdin);
	ret = sendto(fd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
	memset(buffer,0,sizeof(buffer));
	}
	free(buffer);

}
return 0;
}
