#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "funkcije.h"

void WriteOut(int out, char* in)
{
	int i = 0;
	while (in[i] != '\0' || in[i]!= '\n')
	{
		write(out,&in[i++],sizeof(char));
	}
}
