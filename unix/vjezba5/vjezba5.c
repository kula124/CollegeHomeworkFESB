#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    pid_t child, waitret;
	int status = 0;	
	child = fork();
    if (child == 0)
    {
        if (execvp(argv[1], &argv[1]) < 0)
			printf("Exec failed\n");
        _exit(1);
    }
    else if (child > 0)
    {
        waitret = waitpid(child,&status,0);
        printf("Status: %d\n",status);
		return 0;
    }
    else
    {
        perror("fork failed");
        _exit(3);
    }
}