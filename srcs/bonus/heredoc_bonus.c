/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:27:20 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/30 16:16:33 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = -1;
	if (s1 && s2)
		while (s1[++i] || s2[i])
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	make_here_env(int argc, char **argv, t_envs *env)
{
	char	*str;

	env->outfile = argv[argc - 1];
	env->files[1] = open(env->outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (env->files[1] < 0)
		err_handle(env->outfile, 1);
	if (pipe((*env->cmds)->fd) < 0)
		exit (1);
	while (1)
	{
		write(1, "here_doc> ", 11);
		str = get_next_line(1);
		if (!str)
			write(1, "\n", 1);
		if (ft_strcmp(str, argv[2]) == 10)
		{
			free(str);
			break ;
		}
		write((*env->cmds)->fd[1], str, ft_strlen(str));
		free (str);
	}
	(*env->cmds)->fdopen = dup((*env->cmds)->fd[0]);
	close_pipes((*env->cmds)->fd);
}
