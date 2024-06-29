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
	servaddr.sin_port = htons(8080);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	socklen_t setup_len = sizeof(servaddr);
	//ret = connect(fd,(struct sockaddr*)&servaddr,sizeof(servaddr));
       // if(ret < 0){
         //       perror("Connect failed\n");
                return 1;
        }
        else{
                printf("Connected!!\n");
        }

while(1){


	char *buffer = (char*)malloc(1024*sizeof(char));
	printf("Enter Message: ");
	fgets(buffer,100,stdin);
	ret = sendto(fd,buffer,strlen(buffer),0,(struct sockaddr*)NULL,sizeof(servaddr));
	buffer[ret] = '\0';
	memset(buffer,0,strlen(buffer));

	
	ret = recvfrom(fd,buffer,sizeof(buffer),0,(struct sockaddr*)NULL,NULL);
	buffer[ret] = '\0';
	printf("Server: %s\n",buffer);
	
	free(buffer);
}
return 0;
}
