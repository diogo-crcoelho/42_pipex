/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/22 19:03:34 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static char	*find_path(t_envs *env, int idx)
{
	char	**temp;
	char	*teste;
	int		i;

	i = 0;
	temp = ft_split(env->argv[idx], ' ');
	while (env->paths[i])
	{
		teste = join_cmd(env->paths[i++], temp[0]);
		if (access(teste, F_OK) == 0)
		{
			free_pp(temp, 0);
			return (teste);
		}
		free(teste);
	}
	free_pp(temp, 0);
	return (NULL);
}

static void	execute_cmd(t_envs *env, int idx, char **envp)
{
	char	**flagged;
	char	*path;

	flagged = ft_split(env->argv[idx], ' ');
	path = find_path(env, idx);
	execve(path, flagged, envp);
	write(2, "Command not found", 18);
	exit(1);
}

int	pipex(t_envs *env, char **envp)
{
	if (pipe(env->fds) < 0)
		return (-1);
	if (fork() == 0)
	{
		dup2(env->fds[1], 1);
		close_pipes(env->fds);
		dup2(env->files[0], 0);
		execute_cmd(env, 2, envp);
	}
	else
	{
		dup2(env->fds[0], 0);
		close_pipes(env->fds);
		dup2(env->files[1], 1);
		execute_cmd(env, 3, envp);
	}
	close_pipes(env->fds);
	waitpid(-1, NULL, 0);
	return (0);
}
