/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:26:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/18 21:48:33 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	count_paths(char *paths)
{
	int		i;

	i = 1;
	while (*(++paths))
		if (*paths == ':')
			++i;
	return (i);
}

static char	*make_path(char *paths)
{
	int		i;
	char	*path;

	i = 0;
	while (paths[i] && paths[i] != ':')
		++i;
	path = (char *)malloc(i + 1);
	if (!path)
		return (NULL);
	path[i] = 0;
	while (i-- > 0)
		path[i] = paths[i];
	return (path);
}

char	**get_path(char **envp, char *str, int i, int j)
{
	char	**paths;
	int		size;

	while (*envp && i < 3)
	{
		i = -1;
		while (++i < 4)
			if ((*envp)[i] != str[i])
				break ;
		envp += (i != 4);
	}
	size = count_paths(&(*envp)[j]);
	paths = (char **)malloc((size + 1) * sizeof(char *));
	if (!paths)
		return (NULL);
	paths[size] = NULL;
	i = -1;
	while (++i < size)
	{
		paths[i] = make_path(&(*envp)[j]);
		while ((*envp)[j] && (*envp)[j] != ':')
			++j;
		j += ((*envp)[j] == ':');
	}
	return (paths);
}

void	free_path(char **paths)
{
	int	i;
	
	i = 0;
	while (paths[i]){
		free (paths[i++]);
	}
	free (paths);
}