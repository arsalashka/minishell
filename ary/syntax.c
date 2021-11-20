/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:12:11 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:15:31 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static bool	is_com(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

static int	det_type(char a, char b)
{
	if (a == '|')
		return (1);
	else if (a == '>' && b == '>')
		return (2);
	else if (a == '>')
		return (3);
	else if (a == '<' && b == '<')
		return (4);
	else if (a == '<')
		return (5);
	return (-1);
}

static bool	check_fwd(t_com *com, char *line)
{
	int	type;

	type = det_type(line[0], line[1]);
	if (type == 2 || type == 4)
		++line;
	++line;
	line = trim_space(line);
	if (*line == '|')
		com->syntax = 1;
	else if (*line == '>' && line[1] == '>')
		com->syntax = 2;
	else if (*line == '>')
		com->syntax = 3;
	else if (*line == '<' && line[1] == '<')
		com->syntax = 4;
	else if (*line == '<')
		com->syntax = 5;
	if (com->syntax)
		return (true);
	else
		return (false);
}

bool	syntax_err(t_com *com, char *line)
{
	if (*line == '|' || line[ary_strlen(line) - 2] == '|')
	{
		com->syntax = 1;
		return (false);
	}
	while (*line)
	{
		if (*line == '\"' || *line == '\'')
		{
			line = quote_skip(line);
			continue ;
		}
		if (is_com(*line) && line[1] == 0)
		{
			com->syntax = 6;
			return (false);
		}
		if (is_com(*line))
			if (check_fwd(com, line))
				return (false);
		++line;
	}
	return (true);
}

int	countArgc(t_com *com)
{
	t_snode	*head;
	int		ac;

	head = com->arg_start;
	ac = 0;
	while (head)
	{
		++ac;
		if (head)
			head = head->next;
	}
	return (ac);
}
