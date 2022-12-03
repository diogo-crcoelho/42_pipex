/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:26:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/03 20:10:00 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

char	**get_path(char **envp, char *str)
{
	char	**paths;
	int		i;

	i = 0;
	while (*envp && i < 3)
	{
		i = -1;
		while (++i < 4)
			if ((*envp)[i] != str[i])
				break ;
		envp += (i != 4);
	}
	paths = ft_split(&(*envp)[5], ':');
	return (paths);
}

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i++]);
	}
	free(paths);
}
