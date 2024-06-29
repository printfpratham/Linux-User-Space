#include <stdio.h>
#include <unistd.h>



int main()
{
	int ret;
	ret = link("hii.txt","hardlink.txt");
	if(ret != 0)
		perror("hardlink error\n");
	//ret = link("hii.txt","hardlink2.txt");
//	if(ret != 0)
//		perror("hardlink error\n");
}
