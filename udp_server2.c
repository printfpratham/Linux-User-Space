#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define PORT 5000
#define MAXLINE 1000

void *read()
{

	char buffer[MAXLINE];
	int sockfd;
	struct sockaddr_in servaddr, cliaddr;

	bzero(&servaddr, sizeof(servaddr));

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	int len, n;
	len = sizeof(cliaddr);

	while(1) {

		n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
		buffer[n] = '\0';
		printf("Client: %s\n", buffer);

		sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));

	}

	close(sockfd);
}


int main() {

	pthread_t id1;
	int err;

	if((err = pthread_create(&id1,NULL,read,NULL))<0){
		perror("thread not created\n");
		exit(0);
	}


	pthread_join(id1,NULL);

	return 0;
}

