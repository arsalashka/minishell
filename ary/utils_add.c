/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:39:15 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:15:49 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/* utility func for split */

static size_t	ft_split_wctandpos(char const *s, char c, size_t nc)
{
	size_t	wct;
	size_t	pos;

	pos = 0;
	wct = 1;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s != '\0' && pos > 0)
			wct++;
		while (*s != c && *s != '\0')
		{
			s++;
			pos++;
		}
		while (*s == c && *s != '\0')
		{
			s++;
			pos++;
		}
		if (nc > 0 && nc == wct)
			return (pos);
	}
	return (wct);
}

/* frees 2D char* */

static char	**ft_split_free(char **ret)
{
	size_t	ct;

	ct = 0;
	while (ret[ct])
		free(ret[ct++]);
	free(ret);
	return ((void *)0);
}

/* utility func for split */

static char	*ft_split_filler(char const *s, char c, size_t nc, size_t size)
{
	size_t	pos;
	char	*ret;

	if (nc == 0)
		pos = 0;
	else
		pos = ft_split_wctandpos(s, c, nc);
	s += pos;
	while (*s != c && *s != '\0')
	{
		s++;
		size++;
	}
	ret = malloc(size + 2);
	if (!ret)
		return ((void *)0);
	pos = -1;
	s -= size;
	while (size > ++pos)
		ret[pos] = s[pos];
	ret[pos] = '/';
	ret[++pos] = '\0';
	return (ret);
}

/* splits str by char c and return 2D array */

char	**ft_split_ary(char const *s, char c)
{
	size_t	wct;
	size_t	nc;
	char	**ret;

	if (!s)
		return ((void *)0);
	while (*s == c && c != '\0')
		s++;
	nc = 0;
	wct = ft_split_wctandpos(s, c, nc);
	ret = (char **)malloc((wct + 1) * sizeof(char **));
	if (!ret)
		return ((void *)0);
	while (nc < wct)
	{
		ret[nc] = ft_split_filler(s, c, nc, 0);
		if (!ret[nc])
			return (ft_split_free(ret));
		nc++;
	}
	ret[nc] = (void *)0;
	return (ret);
}

bool	empty_line(char *line)
{
	char	*base;

	base = line;
	line = trim_space(line);
	if (!*line)
	{
		free(base);
		return (true);
	}
	return (false);
}
