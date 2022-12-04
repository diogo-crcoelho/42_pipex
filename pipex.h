/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:31:11 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/04 18:44:04 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>

typedef struct s_doraemon
{
	int		argc;
	char	**argv;
	char	**paths;
	char	**cmds;
	char	***flags;
	int		fds[2];
	char	*files[2];
}			t_envs;

char	**get_path(char **envp, char *str);
void free_ppp(char ***ppp);
void free_pp(char **pp);


char	*join_cmd(char *path, char *cmd);
char	**parse_commands(t_envs *env);
size_t	ft_strlen(const char *str);
char	**ft_split(char *str, int sep);

#endif