#include <stddef.h>
#include <unistd.h>

int main()
{
	char path[]="/usr/bin/ls";
	char *vec[]= {"ls", "-l -a", (void *)0};
	execve(path, vec, (void *)0);
}