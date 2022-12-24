/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:31:11 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/23 17:28:25 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				fd[2];
	int				status;
	int				fdopen;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_doraemon
{
	t_cmd			**cmds;
	int				files[2];
	char			*infile;
	char			*outfile;
	char			**envp;
}					t_envs;

char				*get_path(char **env, char *str);
char				**ft_split(char *str, int sep);
void				close_pipes(int fds[2]);
void				err_handle(char *str, int code);
void				free_cmds(t_cmd *head);
void				free_pp(char **pp, int i);
void				pipex(t_envs *env);
t_cmd				**parse_cmds(t_cmd **head, char **argv, char **envp);

#endif