#include "pipex.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>              /* Definition of O_* constants */
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int fds[2];
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_RDWR | O_TRUNC, 0644);
	if (pipe(fds) == -1)
		exit(1);
	int pid = fork();
	if (pid == 0)
	{
		dup2(fds[1],1);
		close(fds[1]);
		close(fds[0]);
		dup2(fd1, 0);
		char *temp[] = {"cat",  NULL};
		execve("/bin/cat", temp, NULL);
	}

	int pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fds[0],0);
		close(fds[0]);
		close(fds[1]);
		dup2(fd2, 1);
		char *temp[] = {"wc", "-l", NULL};
		execve("/usr/bin/wc", temp, NULL);
	}
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, NULL, 0);
	//waitpid(pid2, NULL, 0);
}
//argca
//a