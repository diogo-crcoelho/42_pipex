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

void	execute_cmd(t_envs *env, int idx)
{
	char	**flagged;
	char	*path;

	flagged = ft_split(env->argv[idx], ' ');
	path = find_path(env, idx);
	execve(path, flagged, NULL);
}

void	pipex(t_envs *env)
{
	(void)env;
}

//Estudar forks e pipes
//Ja faltou mais