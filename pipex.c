/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/23 19:45:04 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	execute_cmd(t_cmd *cmd, char **envp)
{
	dup2(cmd->fdopen, 0);
	if (cmd->next)
		dup2(cmd->fd[1], 1);
	close_pipes(cmd->fd);
	execve(cmd->path, cmd->args, envp);
	err_handle(cmd->args[0], 2);
	exit(1);
}

void	pipex(t_envs *env)
{
	t_cmd	*cmds;

	cmds = *env->cmds;
	cmds->fdopen = env->files[0];
	while (cmds)
	{
		if (pipe(cmds->fd) < 0)
			return ;
		dup2(env->files[1], 1);
		if (fork() == 0)
			execute_cmd(cmds, env->envp);
		else
		{
			waitpid(-1, NULL, 0);
			if (cmds->next)
				cmds->next->fdopen = dup(cmds->fd[0]);
			close_pipes(cmds->fd);
			cmds = cmds->next;
		}
	}
}
