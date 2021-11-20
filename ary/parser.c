/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:26:44 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:00:54 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static char	*fill_quote(char *line, char **newline, int *ct, char spec)
{
	if (!find_next_spec(line + 1, spec))
	{
		(*newline)[*ct] = *line;
		++(*ct);
		return (++line);
	}
	++line;
	while (*line != spec)
	{
		(*newline)[*ct] = *line;
		++(*ct);
		++line;
	}
	--(*ct);
	return (++line);
}

static char	*add_arg(t_com *com, char *line, int size)
{
	char	*newline;
	int		ct;

	ct = -1;
	newline = malloc(sizeof(char) * (size + 1));
	if (!newline)
		return (NULL);
	while (++ct < size)
	{
		if (*line == '\'' || *line == '\"')
		{
			line = fill_quote(line, &newline, &ct, *line);
			continue ;
		}
		newline[ct] = *line;
		++line;
	}
	newline[ct] = '\0';
	if (!add_snode(com, newline))
		return (NULL);
	return (line);
}

static bool	duct_tape_parse(t_com *com, char *line, int size)
{
	char	*newline;

	while (*line)
	{
		size = get_size(line);
		if (size == -1)
		{
			line += 2;
			newline = ary_strdup("");
			if (!newline)
				return (false);
			if (!add_snode(com, newline))
				return (false);
			line = trim_space(line);
			continue ;
		}
		if (!size)
			return (true);
		line = add_arg(com, line, size);
		if (!line)
			return (false);
		line = trim_space(line);
	}
	return (true);
}

bool	parse_line(t_com *com, char *line)
{
	line = trim_space(line);
	if (!*line)
	{
		if (!add_snode(com, NULL))
			return (false);
		return (true);
	}
	return (duct_tape_parse(com, line, 0));
}

bool	par_to_parse(t_com *com)
{
	t_par	*par;
	char	*duct;

	par = com->par_head;
	while (par)
	{
		if (!par->line)
		{
			if (!add_snode(com, NULL))
				handleErrors(NULL, false, error_malloc);
		}
		else if (!parse_line(com, par->line))
			handleErrors(NULL, false, error_malloc);
		if (par->next)
		{
			duct = ary_strdup("|");
			if (!duct)
				handleErrors(NULL, false, error_malloc);
			if (!add_snode(com, duct))
				handleErrors(NULL, false, error_malloc);
		}
		par = par->next;
	}
	return (true);
}
