/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_body.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:44:38 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:53:03 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	find_next_spec(char *line, char spec)
{
	while (*line)
	{
		if (*line == spec)
			return (true);
		++line;
	}
	return (false);
}

void	chek_ambig(char *line, int place, t_par *par)
{
	if (place == 0)
		return ;
	--place;
	while (place > 0)
	{
		if (line[place] == ' ' || line[place] == '	')
		{
			--place;
			continue ;
		}
		else
			break ;
	}
	if (line[place] == '<' && (place - 1) != 0 && line[place - 1] != '<')
		par->error = error_ambig;
	else if (line[place] == '>')
		par->error = error_ambig;
}

t_snode	*skip_par(t_snode *node)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
			break ;
		node = node->next;
	}
	return (node);
}

int	is_com_sym(char *line)
{
	if (ary_strcmp("|", line))
		return (1);
	else if (ary_strcmp("<<", line))
		return (2);
	else if (ary_strcmp("<", line))
		return (3);
	else if (ary_strcmp(">>", line))
		return (4);
	else if (ary_strcmp(">", line))
		return (5);
	else
		return (false);
}

void	free_all(t_com *com, t_par *par)
{
	while (com->par_head)
	{
		par = com->par_head;
		com->par_head = par->next;
		if (par->head)
			free_snode(par->head);
		free(par->path);
		free(par->argv);
		free(par->line);
		if (par->error == error_ambig)
		{
			free(par->error_node->value);
			free(par->error_node);
		}
		free(par);
	}
	while (com->ac > 0)
	{
		free(com->av[com->ac]);
		com->ac--;
	}
	free(com->av[0]);
	free_snode(com->arg_start);
	com->par_head = NULL;
	com->arg_start = NULL;
}
