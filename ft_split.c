/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarvalh <dcarvalh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 19:09:06 by dcarvalh          #+#    #+#             */
/*   Updated: 2022/12/02 19:15:06 by dcarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

static char	*ft_strchr(const char *str, int c)
{
	size_t	i;

	i = -1;
	while (str[++i])
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((char *)&str[i]);
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (NULL);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (0);
	if (str[0] && !ft_strchr(str, c))
		return (1);
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i ++;
		if (str[i] && str[i] != c)
			count ++;
		while (str[i] && str[i] != c)
			i ++;
	}
	return (count);
}

static size_t	word_size(const char *str, int n, char c)
{
	size_t	i;

	i = 0;
	while (str[++n] && str[n] != c)
		i ++;
	return (i);
}

static char	*ft_substr(char const *str, unsigned int start, size_t n)
{
	char	*ret;
	size_t	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	if (start >= i)
		n = 0;
	else if (n > (i - start))
		n = i - start;
	ret = (char *)malloc(n + 1);
	if (!ret)
		return (NULL);
	i = -1;
	ret[n] = 0;
	while (++i < n)
		ret[i] = str[start + i];
	return (ret);
}

char	**ft_split(const char *str, char c)
{
	char	**ret;
	int		size;
	int		j;
	int		i;

	i = 0;
	j = -1;
	size = count_words(str, c);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = NULL;
	while (++j < size)
	{
		while (str[i] && str[i] == c)
			i ++;
		if (str[i] && str[i] != c)
			ret[j] = ft_substr(str, i, word_size(str, i - 1, c));
		while (str[i] && str[i] != c)
			i ++;
	}
	return (ret);
}