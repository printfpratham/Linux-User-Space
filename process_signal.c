#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void usr_handler(int sig_num)
{
	printf("Child terminated %d",getpid());
	return;

}


int main()
{
	pid_t ret;
	int status;
	int role = -1;

//	signal(SIGUSR1,usr_handler);
	ret = fork();
	printf("pid : %d\n",ret);
	if(ret == 0){
		printf("this is child process with id: %d\n",getpid());
		sleep(3);
		exit(0);
	}
	else{

		printf("This is parent process with id: %d\n",getpid());
		
		signal(SIGCHLD,usr_handler);
		
		ret = wait(&status);
		}
	return 0;
}


