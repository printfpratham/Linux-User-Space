#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main()
{
	pid_t ret,ext;
	int status,i;
	int role = -1;

	ret = fork();
	if(ret > 0)
	{
		printf("Process Parent with pid %d\n",getpid());
		
		sleep(3);	
		ext = wait(&status);
	
	printf("Ext id: %d\n", ext);
		
	}
	
		//ret = wait(&status);
	else if(ret == 0) {
		printf("This is child process at, Process id= %d\n",getpid());
	
	}
	else{
		printf("Creation failed\n");
	}
	ret = fork();
	
	printf("Ext id- %d\n", ret);
}
