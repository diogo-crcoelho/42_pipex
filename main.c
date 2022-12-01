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
//-1- invalid parameter
//1- malloc error
void	err_handle(int error, t_envs *env)
{
	if (error == -1)
		write(2, "\tInvalid number of parameters", 30);
	else if (error == 2)
	{
		perror(env->files[0]);
		return ;
	}
	else if (error == 3)
		perror(env->files[1]);
	exit(-1);
}

void	make_env(int argc, char **argv, char **envp, t_envs *env)
{
	(void) envp;
	env->cmds = parse_commands(argc, argv);
	if (!(env->cmds))
		err_handle(1, env);
	env->paths = get_path(envp, "PATH", -1, 5);
	if (!(env->paths))	
		err_handle(1, env);
	env->files[0] = argv[1];
	env->files[1] = argv[argc - 1];
	env->fds[0] = open(argv[1], O_RDONLY);
	if (env->fds[0] < 0)
		err_handle(2, env);
	env->fds[1] = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (env->fds[1] < 0)
		err_handle(3, env);

}

int	main(int argc, char **argv, char **envp)
{
	t_envs	env;
	(void)envp;
	if (argc != 5)
		err_handle(-1, &env);
	make_env(argc, argv, envp, &env);
	printf("%s\n", env.paths[0]);
	printf("%s\n", env.cmds[0]);
	free_env(&env);
	return (0);
}
