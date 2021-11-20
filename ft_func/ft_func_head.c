/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_head.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:26:45 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 11:00:05 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/func.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != 0 && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	i;

	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		++i;
	}
	cpy[i] = '\0';
	return (cpy);
}

static int	w_count(char const *s, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			++i;
		if (s[i] && s[i] != c)
			++len;
		while (s[i] && s[i] != c)
			++i;
	}
	return (len);
}

static char	**free_mem(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		w_len;
	int		i;
	int		j;

	strs = (char **)malloc(sizeof(char *) * (w_count(s, c) + 1));
	if (!strs || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && j < w_count(s, c))
	{
		while (s[i] && s[i] == c)
			++i;
		w_len = 0;
		while (s[i + w_len] && s[i + w_len] != c)
			++w_len;
		strs[j] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!strs[j])
			return (free_mem(strs));
		ft_strlcpy(strs[j++], s + i, w_len + 1);
		i += w_len;
	}
	strs[j] = NULL;
	return (strs);
}
