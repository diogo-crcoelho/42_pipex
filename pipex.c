/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/16 19:46:24 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*find_path(t_envs *env, int idx)
{
	char	**temp;
	char	*teste;
	int		i;
	int		x;

	temp = ft_split(env->argv[idx], ' ');
	i = 0;
	while (env->paths[i])
	{
		teste = join_cmd(env->paths[i++], temp[0]);
		x = access(teste, F_OK);
		if (x == 0)
		{
			printf("%s\n", teste);
			free_pp(temp, 0);
			return (teste);
		}
		free(teste);
	}
	free_pp(temp, 0);
	return (NULL);
}

void	execute_cmd(t_envs *env, int idx)
{
	char	**flagged;
	char	*path;

	flagged = ft_split(env->argv[idx], ' ');
	path = find_path(env, idx);
	execve(path, flagged, NULL);
}

//Estudar forks e pipes
//Ja faltou mais