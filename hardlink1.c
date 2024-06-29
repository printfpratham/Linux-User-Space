#include <stdio.h>
#include <unistd.h>
#include <time.h>


int main()
{
	int ret;
	ret = link("hard.txt","hard1.txt");
	if(ret != 0){
		perror("hardlink error\n");
		return 1;
	}
	printf("hardlink success\n");
	
	sleep(5);

	ret = unlink("hard.txt");
	if(ret != 0){
		perror("hardlink unlink error");
		return 1;
	}

	printf("hardlink unlink success\n");
	//ret = link("hii.txt","hardlink2.txt");
//	if(ret != 0)
//		perror("hardlink error\n");
return 0;

}
