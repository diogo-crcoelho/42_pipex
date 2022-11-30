/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:31:11 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/30 17:40:27 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	char	**paths;
	char	**cmds;
	int		fds[2];
	char	*files[2];
}			t_envs;

char		**get_path(char **envp, char *str, int i, int j);
void		free_path(char **paths);
char		*join_cmd(char *path, char *cmd);
char		**parse_commands(int argc, char **argv);

#endif