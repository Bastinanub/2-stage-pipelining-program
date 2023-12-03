#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd[2];
  pipe(fd);

  if (fork() == 0) {
    close(fd[1]); // Close the writing end of the pipe
    dup2(fd[0], 0); // Make the reading end of the pipe the standard input
    close(fd[0]); // Close the original reading end of the pipe
    execlp("cut", "cut", "-d", " ", "-f 1", NULL);
  } else {
    close(fd[0]); // Close the reading end of the pipe
    dup2(fd[1], 1); // Make the writing end of the pipe the standard output
    close(fd[1]); // Close the original writing end of the pipe
    execlp("ls", "ls", "-l", NULL);
  }

  wait(NULL);

  return 0;
}
