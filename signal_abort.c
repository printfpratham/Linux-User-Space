#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void sig_handler(int sig_num)
{
	printf("signal received terminating program\n");
	return ;
}

int main()
{
	int ip;
	signal(SIGABRT,sig_handler);
	
	printf("Press key to give signal\n");
	while(1){
	if(getchar() == 'A'){
	
		abort();
	}
}
	
	pause();
	return 1;
}

