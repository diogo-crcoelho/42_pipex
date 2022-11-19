/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:45:39 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/18 22:07:43 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	**parse_commands(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		size;

	size = argc - 3;
	cmds = (char **)malloc((size + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmds[size] = NULL;
	i = 1;
	while (i++ <= size)
		cmds[i - 2] = argv[i];
	return (cmds);
}

char	*join_cmd(char *path, char *cmd)
{
	int		i;
	int		size;
	char	*joined;
	
	size = 0;
	i = -1;
	while (path[++i])
		++size;
	i = -1;
	while (cmd[++i] && cmd[i] != ' ')
		++size;
	joined = malloc(size + 2);
	if (!joined)
		return (NULL);
	joined[size + 1] = 0;
	while (*path)
		*joined++ = *path++;
	*joined++ = '/';
	while (*cmd)
		*joined++ = *cmd++;
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	**paths;
	char	**cmds;
	int		fd_in;
	int		fd_out;

	if (argc != 5)
	{
		write(2, "\tInvalid number of parameters", 30);
		return (-1);
	}
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC);
	if (fd_in < 0 || fd_out < 0)
	{
		perror("Error opening file");
		return (-1);
	}
	paths = get_path(envp, "PATH", -1, 5);
	cmds = parse_commands(argc, argv);
	join_cmd(paths[0], cmds[0]);
	free(cmds);
	free_path(paths);
	return (0);
}
