/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 05:58:00 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:52:18 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	qute_size(char *line)
{
	char	spec;
	int		size;

	spec = *line;
	++line;
	size = 1;
	while (*line)
	{
		if (*line == spec)
			return (++size);
		++size;
		++line;
	}
	return (1);
}

static int	line_size(char *line)
{
	int		size;
	int		quote;

	size = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quote = qute_size(line);
			size += quote;
			line += quote;
			continue ;
		}
		if (*line == '|')
			return (size);
		++size;
		++line;
	}
	return (size);
}

static void	fill_line(char *newline, char *line, int size)
{
	int		ct;

	ct = -1;
	while (++ct < size)
		newline[ct] = line[ct];
	newline[ct] = '\0';
}

bool	split_line_to_pars(t_com *com, char *line)
{
	t_par	*par;
	int		size;
	char	*newline;

	par = com->par_head;
	while (par)
	{
		size = line_size(line);
		newline = malloc(sizeof(char) * (size + 1));
		if (!newline)
			return (false);
		fill_line(newline, line, size);
		par->line = newline;
		line += size + 1;
		par = par->next;
	}
	return (true);
}
