#include "pipex.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>              /* Definition of O_* constants */
#include <stdlib.h>
#include <sys/wait.h>
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
		close(fds[0]);
		dup2(fds[1],1);
		close(fds[1]);
		dup2(fd1, 0);
		char *temp[] = {"cat",  (void *)0};
		execve("/bin/cat", temp, (void *)0);
	}

	//int pid2 = fork();
	//if (pid2 == 0)
	//{
		close(fds[1]);
		dup2(fds[0],0);
		close(fds[0]);
		//dup2(fd2, 1);
		char *temp[] = {"wc", "-l", (void *)0};
		execve("/usr/bin/wc", temp, (void *)0);
	//}
	close(fds[0]);
	close(fds[1]);
	waitpid(-1, (void *)0, 0);
	//waitpid(pid2, NULL, 0);
}
//argca
//a