#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int status = 0;
	pid_t forked;
	forked = fork();
	wait(&status);
	if (forked == 0)
		printf("\nChild:\n");
	else
		printf("\nParent\n");
	printf("PID =%d\nPPID = %d,\nUID = %d\n----------------\n",getpid(),getppid(),getuid()); 
    return 0;
}