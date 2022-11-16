/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:26:53 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/16 23:31:36 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
char	**get_path(char **envp, char *str)
{
	char	**path;
	int		i;
	
	while (*envp)
	{
		i = -1;
		while (++i < 4)
			if ((*envp)[i] != str[i])
				break;
		if (i == 4)
			break;
		*envp++;
	}
	
	printf("%s", *envp);
}