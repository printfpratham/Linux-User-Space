#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <sys/un.h>


int main()
{
	int fd,new_fd,ret;
	struct sockaddr_un setup;
	ssize_t bytes_rd,bytes_wrt;
	socklen_t addrlen = sizeof(setup);
	char buf[1024] = {0};
	char* path = "/home/pratham/Pratham/Linux-User_Space/unix";


	fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(fd < 0){
		perror("Open error\n");
		return 1;
	}

	setup.sun_family = AF_UNIX;
	setup.sun_path = "/home/pratham/Pratham/Linux-User_Space/unix";
	
	ret = bind(fd,(struct sockaddr*)&setup,sizeof(setup));
	if(ret < 0){
		perror("Bind error\n");
		return 1;
	}

	ret = listen(fd,3);
	if(ret < 0){
		perror("Listen error\n");
		return 1;
	}
	while(1){
	new_fd = accept(fd, (struct sockaddr*)&setup,&addrlen);
	if(ret > 0){
		printf("Client connected\n");
	}
	else{
		perror("Connection error\n");
		return 1;
	}
	bytes_rd = recv(new_fd,buf,100,SOCK_NONBLOCK);
	if(bytes_rd < 0){
		perror("read error\n");
		return 1;
	}
	char* msg = (char*)malloc(bytes_rd*sizeof(char));
	strcpy(msg,buf);
	fputs(msg,stdout);
	memset(buf,0,1024);

	fgets(buf,100,stdin);
	bytes_wrt = send(new_fd,buf,strlen(buf),0);
	if(bytes_wrt < 0){
		perror("Write error\n");
		return 1;
	}
	}
	close(new_fd);
	close(fd);

	return 0;

	


}


