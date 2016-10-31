#include "funkcije3.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int fd, k;
 
  for (k=1; k<argc; k++) {
    fd = open(argv[k], O_RDONLY);
    if (fd == -1) {
      perror("open");
      return -1;
    }
    rw(fd, STDOUT_FILENO);
    close(fd);
  }

  if (k == 1)
    rw(STDIN_FILENO, STDOUT_FILENO);

  return 0;
}
