#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
int main()
{
	// char path[]="/usr/bin/ls";
	// char *vec[]= {"ls", "-l -a", (void *)0};
	// execve(path, vec, (void *)0);
	char **split = ft_split("eu:sou:burro", ':');
	while (*split)
	printf("%s\n", *split++);
}