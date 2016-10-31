#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd1, n, i;
  char sl;
   
  if (argc < 2)
  {
    printf("Koristenje: citaj <ime_datoteke>\n");
    exit(0); //Zasto exit a ne return?
  }
  for (i=1;i<argc;i++)
   {
	   fd1=open(argv[i], O_RDONLY);
	   if (fd1 < 0)
		   printf("Greska prilikom otvaranja %s filea",argv[i]);
  while((n=read(fd1, &sl, 1)) > 0)
     {
       write(STDOUT_FILENO, &sl, 1);
     }
  if (n == -1)
  {
    perror("read");
  }                                                       
  close(fd1);
   }
  return 0;
  }
