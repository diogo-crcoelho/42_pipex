/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:45:39 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/05 16:31:11 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_env(t_envs *env)
{
	free_pp(env->paths);
	free_pp(env->cmds);
	// if (*env->flags)
		free_ppp(env->flags);

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

void	make_env(char **envp, t_envs *env)
{
	(void) envp;
	env->cmds = parse_commands(env);
	if (!(env->cmds))
		err_handle(1, env);
	env->paths = get_path(envp, "PATH");
	if (!(env->paths))
		err_handle(1, env);
	env->files[0] = env->argv[1];
	env->files[1] = env->argv[env->argc - 1];
	env->fds[0] = open(env->files[0], O_RDONLY);
	if (env->fds[0] < 0)
		err_handle(2, env);
	env->fds[1] = open(env->files[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (env->fds[1] < 0)
		err_handle(3, env);
}

int	main(int argc, char **argv, char **envp)
{
	t_envs	env;

	(void)envp;
	if (argc != 5)
		err_handle(-1, &env);
	env.argc = argc;
	env.argv = argv;
	make_env(envp, &env);
	// env.cmds = parse_commands(&env);
	// int i =-1;
	// while(env.cmds[++i]){
	// 	printf("cmd:%s-flags:", env.cmds[i]);
	// 	while(*env.flags[i])
	// 		// printf("cmd:%s-flags:%s\n", env.cmds[i], env.flags[0][0]);
	// 		printf("%s...", *env.flags[i]++);
	// 	printf("\n");
	// }
	free_env(&env);			
	return (0);
}
