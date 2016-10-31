#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "funkcije.h"
int main(int argc, char** argv)
{
	int i = 1;
	int file_ = 0; 
	char c, buffer[50];
	if (argc<2 || argc > 2)
	{
		exit(1);
		strcpy(buffer,"Bad argument");
		WriteOut(STDOUT_FILENO,buffer);
	}
	file_ = open (argv[i],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); //stvara datoteku sa pravima 775
	if (file_ <0) // ako file nije otvoren 
	{
		exit(file_);
		strcpy(buffer,"Can't open file");
		WriteOut(STDOUT_FILENO,buffer);
	}
	read(STDIN_FILENO,&c,sizeof(c)); //citaj sa standardong ulaza velicinu c u byteovima i spremi ga u c
	write(file_,&c,sizeof(c)); //pisi u file_ sadrzaj od c velicine c byteova
	close (file_);
	strcpy(buffer,"Done\n");
	WriteOut (STDOUT_FILENO,buffer);
	return 0;
}
