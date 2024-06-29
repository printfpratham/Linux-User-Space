#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>


#define PORT 8080


int main()
{
	int fd,new_fd,ret;
	int opt = 1;
	fd_set rset;
	struct sockaddr_in add;
	socklen_t addrlen = sizeof(add);
	char* buffer;
	char first[100];
	char* hello;
	ssize_t data,bytes_sent;
	
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd < 0){
		perror("Socket creation error!\n");
		return 1;
	}

	if (setsockopt(fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(PORT);

	ret = bind(fd,(struct sockaddr *)&add,sizeof(add));
	if(ret < 0){
		perror("Bind error\n");
		return 1;
	}

	ret = listen(fd , 10);
	if(ret < 0){
		perror("Listen failure\n");
		return 1;

	}

	new_fd = accept(fd , (struct sockaddr *)&add,&addrlen);
	if(new_fd < 0){
		perror("Accept error\n");
		return 1;
	}
	else{
		printf("Connected to Client\n");
	}
	
	data = read(new_fd,first,100);
	printf("%s,bytes received: %d\n",first,data);
	
	hello = (char*)malloc(2048*sizeof(char));
	printf("Enter msg\n");
		
	
	
	
	

	while(1)
	{

		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(new_fd,&rset);
		
		ret = select(new_fd+1,&rset,NULL,NULL,NULL);	
		
		if(FD_ISSET(0,&rset)){
		fgets(hello,100,stdin);
		bytes_sent = send(new_fd, hello,strlen(hello),0);
		memset(hello,0,strlen(hello));
		}

		if(FD_ISSET(new_fd,&rset)){
		data = recv(new_fd,hello,100,SOCK_NONBLOCK);
		buffer = (char*)malloc(data*sizeof(char));
		strcpy(buffer,hello);
		
		printf("Client: %s\n",buffer);
		memset(buffer,0,strlen(buffer));
		}
	}



		
	
	free(hello);
	free(buffer);
	close(new_fd);
	close(fd);
	return 0;
}

