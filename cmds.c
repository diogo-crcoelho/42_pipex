/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:34:46 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/02 17:16:33 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

static char	*sep_cmds(t_envs *env, int idx)
{
	int		size1;
	int		size2;
	int		i;
	char	*cmds;

	i = 0;
	size1 = 0;
	while (env->argv[idx][i] && env->argv[idx][i++] != ' ')
		++size1;
	cmds = malloc(size1 + 1);
	cmds[size1] = 0;
	size2 = 0;
	while (env->argv[idx][++i])
		++size2;
	env->flags[idx - 2] = malloc(size2);
	env->flags[idx - 2][size2] = 0;
	if (!(cmds && env->flags))
		return (NULL);
	while (*env->argv[idx] && *env->argv[idx] != ' ')
		*cmds++ = *env->argv[idx]++;
	while (*env->argv[idx])
		*env->flags[idx - 2]++ = *env->argv[idx]++;
	env->flags[idx - 2] -= (size2 + 1);
	return (cmds - size1);
}

char	**parse_commands(t_envs *env)
{
	char	**cmds;
	int		i;
	int		size;

	size = env->argc - 3;
	cmds = (char **)malloc((size + 1) * sizeof(char *));
	env->flags = (char **)malloc((size + 1) * sizeof(char *));
	if (!cmds || !(env->flags))
		return (NULL);
	cmds[size] = NULL;
	i = 1;
	while (i++ <= size)
		cmds[i - 2] = sep_cmds(env, i);
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

