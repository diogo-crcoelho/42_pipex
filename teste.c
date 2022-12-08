#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
int main()
{
	char path[]="/usr/bin/ls";
	char **flags = ft_split("ls -l -a", ' ');
	execve(path, flags, (void *)0);
	// char **split = ft_split("eu:sou:burro", ':');
	// while (*split)
	// printf("%s\n", *split++);
}