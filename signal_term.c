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
	signal(SIGTERM,sig_handler);
	while(1){
	printf("Press key to give signal\n");
	if(getchar() == 'A'){
	//scanf("%d",&ip);
	//while(ip == 1){
		abort();
	}
	}
	
	
	return 1;
}

