#include <stdio.h>
#include <signal.h>
#include <unistd.h>


void sig_handler(int sig_num)
{
	printf("signal received\n");
	return;
}

int main()
{
	while(1){
	printf("Press key to give signal\n");
	signal(SIGINT,sig_handler);
	sleep(1);
	}
}

