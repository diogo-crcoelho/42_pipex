/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:31:11 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/02 16:49:08 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_doraemon
{
	int		argc;
	char	**argv;
	char	**paths;
	char	**cmds;
	char	**flags;
	int		fds[2];
	char	*files[2];
}			t_envs;

char		**get_path(char **envp, char *str, int i, int j);
void		free_path(char **paths);
char		*join_cmd(char *path, char *cmd);
char		**parse_commands(t_envs *env);

#endif