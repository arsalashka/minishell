/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:39:33 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:16:31 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/* strlen */

int	ary_strlen(char *s)
{
	int	ct;

	ct = -1;
	while (s[++ct])
		;
	return (ct);
}

/* strdup */

char	*ary_strdup(char *src)
{
	char	*ret;
	int		len;

	len = ary_strlen(src);
	ret = malloc(sizeof(char) * ++len);
	if (!ret)
		return (NULL);
	while (len-- > 0)
		ret[len] = src[len];
	return (ret);
}

/* strcmp but in boolean */

bool	ary_strcmp(char *src, char *trgt)
{
	if ((!src && !trgt) || (src == trgt))
		return (true);
	if (!src || !trgt)
		return (false);
	while (*src && *trgt)
	{
		if (*src != *trgt)
			return (false);
		++src;
		++trgt;
	}	
	if (*src != *trgt)
		return (false);
	return (true);
}

/* also tabs....lol */

char	*trim_space(char *line)
{
	while (*line == ' ' || *line == '	')
		++line;
	return (line);
}

/* what did it do? */

int	make_file(char *name)
{
	int	fd;

	fd = open(name, O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}
