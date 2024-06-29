#include <stdio.h>
#include <unistd.h>


int main()
{
	int ret;
	ret  = symlink("softlink.txt","softlink1.txt");
	if(ret != 0)
		perror("Softlink error");
	printf("Softlink sucess\n");
	return 0;
}

