/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:34:46 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/30 17:39:27 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**parse_commands(int argc, char **argv)
{
	char	**cmds;
	int		i;
	int		size;

	size = argc - 3;
	cmds = (char **)malloc((size + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmds[size] = NULL;
	i = 1;
	while (i++ <= size)
		cmds[i - 2] = argv[i];
	return (cmds);
}

char	*join_cmd(char *path, char *cmd)
{
	int		i;
	int		size;
	char	*joined;

	size = 0;
	i = -1;
	while (path[++i])
		++size;
	i = -1;
	while (cmd[++i] && cmd[i] != ' ')
		++size;
	joined = malloc(size + 2);
	if (!joined)
		return (NULL);
	joined[size + 1] = 0;
	while (*path)
		*joined++ = *path++;
	*joined++ = '/';
	while (*cmd)
		*joined++ = *cmd++;
	return (joined - size);
}