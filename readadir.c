#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main()
{
	DIR* dirp;
	struct dirent *dirread;
	dirp = opendir("/home/pratham");
	if(dirp == NULL){
		perror("Directory open error\n");
		return 1;
	}

	while((dirread = readdir(dirp))!=NULL)
	{	
	printf("inode no: %d , contents: %s,  type: %c\n",dirread->d_ino,dirread->d_name,dirread->d_type);
	
	}

	closedir(dirp);
	return 0;


}








