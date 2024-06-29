#include <stdio.h>
#include <unistd.h>
#include <errno.h>


int main()
{
	pid_t ret;

	ret = fork();
	printf("Hello, pid= %d\n", ret);
	ret = fork();
	printf("%d\n",ret);
	ret = fork();
	printf("%d\n",ret);
	ret = fork();
	printf("%d\n",ret);
	printf("Hello| pid= %d\n",ret);

}
