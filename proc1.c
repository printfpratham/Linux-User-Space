#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
	pid_t myPid;
	pid_t myparentid;
	gid_t myGid;
	uid_t myUid;


	myPid = getpid();
	myparentid = getppid();
	myGid = getgid();
	myUid = getuid();

	printf("Process id is: %d\n",myPid);
	printf("Parent id: %d\n",myparentid);
	printf("Group id: %d\n",myGid);
	printf("user id: %d\n",myUid);

	return 0;
}
