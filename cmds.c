/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:34:46 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/08 19:52:07 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char	**parse_commands(t_envs *env)
{
	char	**cmds;
	int		i;
	int		size;

	size = env->argc - 3;
	cmds = (char **)malloc((size + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmds[size] = NULL;
	i = 1;
	while (i++ <= size)
	{
		// char **temp = ft_split(env->argv[i], ' ');
		cmds[i - 2] = env->argv[i];
		// free_pp(temp, 1);
	}
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
	while (*cmd && *cmd != ' ')
		*joined++ = *cmd++;
	return (joined - (size + 1));
}
