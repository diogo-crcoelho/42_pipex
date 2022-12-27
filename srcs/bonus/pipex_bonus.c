/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/27 15:16:13 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

static void	execute_cmd(t_cmd *cmd, char **envp)
{
	prot_dup2(cmd->fdopen, 0);
	if (cmd->next)
		prot_dup2(cmd->fd[1], 1);
	close_pipes(cmd->fd);
	execve(cmd->path, cmd->args, envp);
	err_handle(cmd->args[0], 2);
	exit(1);
}

static void	pipex(t_envs *env, int flag)
{
	t_cmd	*cmds;
	int		pid;

	cmds = *env->cmds;
	if (!flag)
		cmds->fdopen = env->files[0];
	while (cmds)
	{
		if (pipe(cmds->fd) < 0)
			return ;
		prot_dup2(env->files[1], 1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
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
	int				here;

	here = !(ft_strcmp(argv[1], "here_doc"));
	if (argc <= 3 + here)
		err_handle("", -1);
	env.envp = envp;
	env.cmds = parse_cmds(&cmds, argv, envp, 2 + here);
	if (!here)
		make_env(argc, argv, &env);
	else
		make_here_env(argc, argv, &env);
	pipex(&env, here);
	free_cmds(*env.cmds);
	return (0);
}
