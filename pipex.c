/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/15 20:30:14 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

char *find_path(t_envs *env, int idx)
{
	char **temp = ft_split(env->argv[idx], ' ');
	char *teste;
	int i = 0;
	while(env->paths[i]){
		teste = join_cmd(env->paths[i++], temp[0]);
		int x = access(teste, F_OK);
		if (x == 0){
			printf("%s\n", teste);
			free_pp(temp, 0);
			return (teste);
		}
		free (teste);
	}
	free_pp(temp, 0);
	return (NULL);
}

void execute_cmd(t_envs *env, int idx)
{
	char **flagged = ft_split(env->argv[idx], ' ');
	char *path = find_path(env, idx);

	execve(path, flagged, NULL);
}