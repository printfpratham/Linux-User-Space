#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char* str;
	//str = (char*)malloc(1*sizeof(char));
	str = strdup("hello world\n");	
	if(str == NULL){
		perror("memory not allocated\n");
		return 1;
	}
	printf("%s",str);
	free(str);
}

