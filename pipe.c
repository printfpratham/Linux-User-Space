#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
void handler(int sig_num)
{
	printf("Child terminated\n");
}


int main(int argc, char* argv[])
{
	int pipefd[2];
	ssize_t bytesrd, byteswrt;
	pid_t ret;
	char buf;

	int stat = pipe(pipefd);

	if(stat<0){
		perror("pipe error\n");
		return 1;
	}

	ret = fork();
	signal(SIGCHLD,handler);
	if(ret < 0){
		perror("fork error\n");
		return 1;
	}

	if(ret == 0){
		printf("child process started %d\n",getpid());
		close(pipefd[1]);
		while(read(pipefd[0],&buf,1)>0){

			write(STDOUT_FILENO,&buf,1);
		}
			write(STDOUT_FILENO,"\n",1);
		
		close(pipefd[0]);
	}


	else{

		printf("Parent started with id: %d\n",getpid());
		close(pipefd[0]);
		write(pipefd[1],argv[1],strlen(argv[1]));
		close(pipefd[1]);
		wait(NULL);
	}

}
		
			
		


