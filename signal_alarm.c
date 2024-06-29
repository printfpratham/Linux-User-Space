#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void sig_handler(int sig_num)
{
	printf("signal received 3 seconds elapsed program\n");
	return ;
}

int main()
{
	int ip;
	signal(SIGALRM,sig_handler);
	printf("Press key to give signal\n");
	getchar();
	alarm(3);
	

	pause();
	return 1;
}

