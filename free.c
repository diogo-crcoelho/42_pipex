/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 14:43:58 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/05 16:37:41 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>


void free_pp(char **pp)
{
	int	i;

	i = 0;
	while (pp[i])
	{
		free(pp[i++]);
	}
	free(pp);
}

void free_ppp(char ***ppp)
{
	int	i;

	i = 0;
	while (ppp[i])
	{
		write(1,"a",1);
		free_pp(ppp[i++]);
	}
	free(ppp);
}