/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/08 20:52:09 by dcarvalh         ###   ########.fr       */
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
	char *cmd = temp[0];
	int i = 0;
	free_pp(temp, 1);
	while(env->paths[i]){
		teste = join_cmd(env->paths[i++], cmd);
		int x = access(teste, F_OK);
		if (x == 0){
			printf("%s\n", teste);
			free(cmd);
			return (teste);
		}
		free (teste);
	}
	free(cmd);
	return (NULL);
}
