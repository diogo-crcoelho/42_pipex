/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2023/01/03 17:10:30 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static void	execute_cmd(t_envs *env, t_cmd *cmd, char **envp)
{
	char	*path;

	path = cmd->path;
	if (dup2(cmd->fdopen, 0) != -1)
	{
		if (cmd->next)
			prot_dup2(cmd->fd[1], 1);
		else
			prot_dup2(env->files[1], 1);
		close_pipes(cmd->fd);
		if (!cmd->path)
			path = cmd->args[0];
		execve(path, cmd->args, envp);
		err_handle(cmd->args[0], 2);
	}
	free_cmds(env->cmds);
	exit(1);
}

static void	pipex(t_envs *env)
{
	t_cmd	*cmds;
	int		pid;

	cmds = *env->cmds;
	cmds->fdopen = env->files[0];
	while (cmds)
	{
		if (pipe(cmds->fd) < 0)
			exit (1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			execute_cmd(env, cmds, env->envp);
		else
		{
			if (cmds->next)
				cmds->next->fdopen = dup(cmds->fd[0]);
			close_pipes(cmds->fd);
			cmds = cmds->next;
		}
	}
}

static void	make_env(int argc, char **argv, t_envs *env)
{
	env->infile = argv[1];
	env->outfile = argv[argc - 1];
	env->files[0] = open(env->infile, O_RDONLY);
	if (env->files[0] < 0)
		err_handle(env->infile, 0);
	env->files[1] = open(env->outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (env->files[1] < 0)
		err_handle(env->outfile, 1);
}

int	main(int argc, char **argv, char **envp)
{
	static t_envs	env;
	static t_cmd	*cmds;
	int				i;

	if (argc != 5)
		err_handle("", -1);
	env.envp = envp;
	make_env(argc, argv, &env);
	env.cmds = parse_cmds(&cmds, argv, envp);
	pipex(&env);
	i = -1;
	while (++i < argc - 3)
		waitpid(-1, NULL, 0);
	free_cmds(env.cmds);
	return (0);
}
