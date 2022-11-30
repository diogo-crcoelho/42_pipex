/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:45:39 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/30 17:41:30 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_env(t_envs *env)
{
	free(env->cmds);
	free_path(env->paths);
}

void	err_handle(int error, t_envs *env)
{
	if (error == -1)
		write(2, "\tInvalid number of parameters", 30);
	else if (env->fds[0] < 0)
		perror(env->files[0]);
			exit(-1);
}

void	make_env(void)
{
	
}
int	main(int argc, char **argv, char **envp)
{
	t_envs	env;

	if (argc != 5)
		err_handle(-1, &env);
	env.fds[0] = open(argv[1], O_RDONLY);
	env.fds[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (env.fds[0] < 0 || env.fds[1] < 0)
		err_handle(0, &env);
	env.paths = get_path(envp, "PATH", -1, 5);
	env.cmds = parse_commands(argc, argv);
	free_env(&env);
	return (0);
}
