/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:26:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/16 19:46:49 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	get_path(t_envs *env, char **envp, char *str)
{
	int	i;

	i = 0;
	while (*envp && i < 3)
	{
		i = -1;
		while (++i < 4)
			if ((*envp)[i] != str[i])
				break ;
		envp += (i != 4);
	}
	env->paths = ft_split(&(*envp)[5], ':');
}
