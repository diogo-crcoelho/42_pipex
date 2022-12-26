/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:45:39 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/23 19:45:37 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

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

	if (argc != 5)
		err_handle("", -1);
	env.envp = envp;
	make_env(argc, argv, &env);
	env.cmds = parse_cmds(&cmds, argv, envp);
	pipex(&env);
	free_cmds(*env.cmds);
	return (0);
}
