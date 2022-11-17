/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:38:13 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/11/17 20:39:37 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "pipex.h"

#include <stdio.h>

int main(int argc, char *argv[], char **envp)
{
	char *PATH = envp[38];
	
	printf("%s\n", PATH);

	char  **paths= get_path(envp, "PATH", 5);
	while (*paths)
	{
		printf("%s\n", *paths++);
	}
}