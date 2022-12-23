/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:34:46 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/23 18:01:16 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

static char	*join_cmd(char *path, char *cmd)
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
	while (*cmd && *cmd != ' ')
		*joined++ = *cmd++;
	return (joined - (size + 1));
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*teste;
	int		i;

	i = 0;
	paths = ft_split(get_path(envp, "PATH"), ':');
	while (paths[i])
	{
		teste = join_cmd(paths[i++], cmd);
		if (access(teste, F_OK) == 0)
		{
			free_pp(paths, 0);
			return (teste);
		}
		free(teste);
	}
	free_pp(paths, 0);
	return (NULL);
}

static t_cmd	*create_cmd(char *command, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = ft_split(command, ' ');
	cmd->path = find_path(cmd->args[0], envp);
	cmd->status = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	**parse_cmds(t_cmd **head, char **argv, char **envp)
{
	t_cmd	*tmp;
	t_cmd	*end;
	int		i;

	i = 2;
	end = NULL;
	while (argv[i + 1])
	{
		tmp = create_cmd(argv[i++], envp);
		if (!(*head))
			*head = tmp;
		if (end)
			end->next = tmp;
		end = tmp;
	}
	return head;
}