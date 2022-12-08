/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/08 20:24:23 by dcarvalh         ###   ########.fr       */
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
	while(*env->paths){
		teste = join_cmd(*env->paths++, cmd);
		int x = access(teste, F_OK);
		if (x == 0){
			printf("%s\n", teste);
			return (teste);
		}
		free (teste);
	}
	return (NULL);
}
