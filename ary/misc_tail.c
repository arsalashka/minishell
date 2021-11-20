/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_tail.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:03:14 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:55:45 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	err_set(t_par *par, int error)
{
	par->error = error;
	return (false);
}

static char	*quote(char *line, int *size)
{
	char	*base;
	char	spec;
	int		len;

	spec = *line;
	++line;
	base = line;
	len = 0;
	while (*line)
	{
		if (*line == spec)
		{
			(*size) += len;
			return (++line);
		}
		++line;
		++len;
	}
	++(*size);
	return (base);
}

int	get_size(char *line)
{
	int	size;

	if ((line[0] == '<' && line[1] == '<')
		|| (line[0] == '>' && line[1] == '>'))
		return (2);
	if (*line == '|' || *line == '<' || *line == '>')
		return (1);
	size = 0;
	while (*line)
	{
		if (*line == ' ')
			break ;
		if (*line == '|' || *line == '<' || *line == '>')
			break ;
		if (*line == '\'' || *line == '\"')
		{
			if (line[1] == *line)
				return (-1);
			line = quote(line, &size);
			continue ;
		}
		++line;
		++size;
	}
	return (size);
}

char	*sq_qutes(char *line)
{
	char	spec;
	char	*start;

	spec = *line;
	++line;
	start = line;
	if (!*line)
		return (line);
	while (*line)
	{
		if (*line == spec)
			return (++line);
		++line;
	}
	return (start);
}
