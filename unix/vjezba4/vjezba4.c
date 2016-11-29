#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX 50
int main(void)
{
	int status = 0;
	int myPID;
    int forkPID;
	int parentPID;
	int userID;
    forkPID = fork();
	wait(&status);
	if(forkPID >= 0) // fork was successful
    {
        if(forkPID == 0) // child process
        {
            myPID = getpid();
			parentPID = getppid();
			userID = getuid();
			write (STDOUT_FILENO,"Process child :\n",MAX);
			printf("C - MY PID: %d \nC - MY PPID: %d \nC - MY USERID: %d \n",myPID,parentPID,userID);
        }
        else //Parent process
        {
            myPID = getpid();
			parentPID = getppid();
			userID = getuid();
			write (STDOUT_FILENO,"Process parent :\n",MAX);
			printf("P - MY PID: %d\nP - MY PPID: %d\nP - MY USERID: %d\n",myPID,parentPID,userID);
        }
    }
    else // fork failed
    {
        printf("\n Fork failed, quitting!!!!!!\n");
        return 1;
    }
    return 0;
}