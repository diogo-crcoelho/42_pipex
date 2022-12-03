/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:09:06 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/03 19:51:37 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

static int	word_count(char *str, int sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == sep)
			++i;
		if (str[i] != '\0')
			++count;
		while (str[i] != '\0' && str[i] != sep)
			++i;
	}
	return (count);
}

static char	*ft_word(char *str, int sep)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != sep)
		++i;
	word = malloc(i + 1);
	if (!word)
		return (NULL);
	word[i] = 0;
	while (i--)
	{
		word[i] = str[i];
	}
	return (word);
}

char	**ft_split(char *str, int sep)
{
	char	**strings;
	int		size;
	int		i;
	int		j;

	if (!str)
		size = 0;
	else
		size = word_count(str, sep);
	strings = malloc((size + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	strings[size] = NULL;
	i = 0;
	j = 0;
	while (j < size)
	{
		while (str[i] != '\0' && str[i] == sep)
			++i;
		if (str[i] != '\0')
			strings[j++] = ft_word(&str[i], sep);
		while (str[i] != '\0' && str[i] != sep)
			++i;
	}
	return (strings);
}
