#include "socket_inc.h"


#define PORT 8080

void* handle_client(void* arg);
pthread_mutex_t mut;

int main()
{
	int fd,new_fd,ret;
	int opt = 1;
	int count = 0;
	fd_set rset;
	struct sockaddr_in add;
	socklen_t addrlen = sizeof(add);
	pthread_t thread1;

	ret = pthread_mutex_init(&mut,NULL);
	if(ret < 0){
		perror("Mutex init error\n");
		return 1;
	}

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
	while(1){
	new_fd = accept(fd , (struct sockaddr *)&add,&addrlen);
	if(new_fd < 0){
		perror("Accept error\n");
		return 1;
	}

	else{
		count++;
		printf("Connected to Client!! %d having ip: %s\n",count,inet_ntoa(add.sin_addr));
	}
	ret = pthread_create(&thread1,NULL,handle_client,&new_fd);
	if(ret != 0){
		perror("Thread Creation error\n");
		return 1;
	}	
	}
	close(fd);
	
}



void* handle_client(void* arg)
{
	int serv_fd = (*(int*)arg);
	fd_set rset;
	int data;
while(1){

	char *buffer = (char*)malloc(1024*sizeof(char));
	 	FD_ZERO(&rset);
                FD_SET(0,&rset);
                FD_SET(serv_fd,&rset);
	
	int ret = select(serv_fd+1,&rset,NULL,NULL,NULL);
	if(serv_fd > 0){
	printf("Fd selected: %d\n",serv_fd);
	}
	
	if(FD_ISSET(serv_fd,&rset)){

	data = recv(serv_fd,buffer,100,SOCK_NONBLOCK);
	if(data < 0){
		perror("Read Error\n");
		exit(1);
	}
	buffer[data] = '\0';
	printf("Client %d :%s\n",serv_fd,buffer);
	memset(buffer,0,strlen(buffer));

	}
	

	if(FD_ISSET(0,&rset)) {

	fgets(buffer,100,stdin);
	data = send(serv_fd,buffer,strlen(buffer),0);
	memset(buffer,0,strlen(buffer));
	}
	free(buffer);

}
	
	close(serv_fd);
	return NULL;
}



