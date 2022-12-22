/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:31:11 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/22 16:34:44 by dcarvalh         ###   ########.fr       */
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
	int		fds[2];
	int		files[2];
	char	*infile;
	char	*outfile;
}			t_envs;

void		get_path(t_envs *env, char **envp, char *str);
void		free_pp(char **pp, int i);
// char		*find_path(t_envs *env, int idx);
char		*join_cmd(char *path, char *cmd);
char		**parse_commands(t_envs *env);
// size_t	ft_strlen(const char *str);
char		**ft_split(char *str, int sep);
// void		execute_cmd(t_envs *env, int idx);
void		close_pipes(int fds[2]);
int			pipex(t_envs *env);

#endif