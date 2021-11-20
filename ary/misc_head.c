/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:22:13 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:54:22 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char	*quote_skip(char *line)
{
	char	spec;
	char	*base;

	spec = *line;
	++line;
	base = line;
	while (*line)
	{
		if (*line == spec)
			return (++line);
		++line;
	}
	return (base);
}

int	alt_quote_skip(char *line)
{
	int		ct;
	char	spec;

	ct = -1;
	spec = *line;
	++line;
	if (*line == spec)
		return (1);
	while (line[++ct])
		if (line[ct] == spec)
			return (ct + 2);
	return (1);
}

bool	chek_line(char s)
{
	if (s == '-' || s == '?' || s == '*' || s == '$'
		|| s == '@' || s == '_' || s == '#'
		|| s == '!' || (s >= '0' && s <= '9')
		|| (s > 64 && s < 91) || (s > 96 && s < 123))
		return (true);
	return (false);
}

bool	chek_back(char *line, char *base)
{
	if (line == base)
		return (true);
	--line;
	while (line != base)
	{
		if (*line == ' ' || *line == '	')
		{
			--line;
			continue ;
		}
		if (*line != '<')
			return (true);
		else
		{
			--line;
			if (*line == '<')
				return (false);
			else
				return (true);
		}
	}
	return (true);
}

bool	chek_empty(char *line)
{
	line = trim_space(line);
	if (!*line)
		return (true);
	else
		return (false);
}
