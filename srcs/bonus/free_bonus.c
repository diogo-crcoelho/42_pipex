/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:43:58 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/27 15:19:02 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	free_pp(char **pp, int i)
{
	if (i >= 0)
		while (pp[i])
			free(pp[i++]);
	free(pp);
}

void	close_pipes(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	free_cmds(t_cmd *head)
{
	t_cmd	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		free_pp(temp->args, 0);
		free(temp->path);
		head = temp->next;
		free(temp);
	}
}

void	err_handle(char *str, int code)
{
	if (code == -1)
		write(2, "\tInvalid number of parameters", 30);
	else if (code == 0)
	{
		perror(str);
		return ;
	}
	else if (code == 1)
		perror(str);
	else if (code == 2)
	{
		while (*str)
			write(2, str++, 1);
		write(2, ": Command not found\n", 21);
	}
	exit(1);
}

void	prot_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
		exit(1);
}
