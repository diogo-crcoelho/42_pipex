/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/19 20:43:21 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void	execute_cmd(t_envs *env, int idx)
{
	char	**flagged;
	char	*path;

	flagged = ft_split(env->argv[idx], ' ');
	path = find_path(env, idx);
	execve(path, flagged, NULL);
}

int	pipex(t_envs *env)
{
	if (pipe(env->fds) < 0)
		return (-1);
	if (fork() == 0)
	{
		dup2(env->fds[1], 1);
		close_pipes(env->fds);
		dup2(env->files[0], 0);
		execute_cmd(env, 2);
	}
	else
	{
		dup2(env->fds[0], 0);
		close_pipes(env->fds);
		dup2(env->files[1], 1);
		execute_cmd(env, 3);
	}
	close_pipes(env->fds);
	waitpid(-1, NULL, 0);
	return (0);
}
