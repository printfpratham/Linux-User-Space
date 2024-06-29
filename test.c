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
	printf("Press key to give signal\n");
       	int a = signal(SIGINT,sig_handler);
	pause();
	printf("a: %d\n",a);	
	a = signal(SIGALRM,sig_handler);
	alarm(5);
	pause();

	printf("b: %d\n",a);
	
}

