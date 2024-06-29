#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <sys/select.h>

int main(void)
{
	int s_id,status,size;
	fd_set rset;
	ssize_t bytes_rd,bytes_wrt;
	char *ch = "Hello from Client\n";
	struct sockaddr_in addr;
	char *buf = (char *)malloc(1024*sizeof(char));

	s_id = socket(AF_INET, SOCK_STREAM, 0);
        if(s_id == -1){
                perror("Error s_id");
                exit(1);
        }

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);

        if((inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)) == -1){
		perror("Error pton");
		exit(1);
	}
	
	status = connect(s_id, (struct sockaddr*)&addr, sizeof(addr));
	if(status < 0){
		perror("Error connect");
		exit(1);
	}
	else{
		printf("Connected to server!!\n");
	}
	bytes_wrt = send(s_id, ch, strlen(ch), 0);
	if(bytes_wrt > 0){
		printf("Hello message sent\n");
	}
	else{
		perror("Message send failed\n");
		return 1;
	}
	
	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(0,&rset);
		FD_SET(s_id,&rset);

		select(s_id+1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(0,&rset)){
		fgets(buf,1024,stdin);
		send(s_id, buf, strlen(buf), 0);
		memset(buf,0,strlen(buf));
		}
		
		if(FD_ISSET(s_id,&rset)){
		size = recv(s_id, buf, 1024,SOCK_NONBLOCK);
			if((buf[0] == '\0')||(size == 0)){
			close(s_id);
			return 1;
			}
		buf[size] = '\0';
		printf("Server: %s",buf);
		memset(buf,0,strlen(buf));
		
	}
	}
	close(s_id);

	free(buf);
	return 0;
}
