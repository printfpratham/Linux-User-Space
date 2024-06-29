#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("Process 1\n");
	fork();
	printf("Process 2\n");
	fork();
	printf("Process 3\n");
	fork();
	printf("Process 4\n");
}
