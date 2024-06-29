#include <stdio.h>
#include <unistd.h>



int main()
{
	int ret;
	ret = link("softlink.txt","soft_frm_hard.txt");
	if(ret != 0)
		perror("hardlink error\n");
	printf("Softlink from hardlink success\n");
		return 0;
}
