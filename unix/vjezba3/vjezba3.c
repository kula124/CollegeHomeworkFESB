#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int file_ = 0; 
	int bytesRead;
	char c;
	int i = 0;
	if (argc < 2)
	{
		printf("Usage: [%s] filename.txt\n",argv[0]);
		exit(1);
	}
	while (++i < argc) //Pokusaj pisati u vise datoteka
	{
		file_ = open (argv[i],O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); //stvara datoteku sa pravima 775
		if (file_ <0) // ako file nije otvoren 
		{
			printf("Can't open file\n");
			exit(file_);
		}
		while (1)
		{
			bytesRead = read(STDIN_FILENO,&c,1);
			if (c == '0' || bytesRead <= 0)
				break;
			write(file_,&c,1);
		}	
		close(file_);
	}
	return 0;
}
