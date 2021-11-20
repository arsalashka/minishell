/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 05:52:10 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:56:54 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static void	init_node(t_par *newnode)
{
	newnode->head = NULL;
	newnode->in_node = NULL;
	newnode->out_node = NULL;
	newnode->head = NULL;
	newnode->next = NULL;
	newnode->path = NULL;
	newnode->exe = NULL;
	newnode->heredoc = false;
	newnode->input_err = false;
	newnode->append = false;
	newnode->built_in = false;
	newnode->error = 0;
	newnode->fd_hd = 0;
	newnode->fd_in = 0;
	newnode->fd_out = 1;
}

static bool	add_par_node(t_com *com)
{
	t_par	*newnode;

	newnode = malloc(sizeof(t_par));
	if (!newnode)
		return (false);
	init_node(newnode);
	if (!com->par_head)
	{
		com->par_head = newnode;
		com->par_tail = newnode;
	}
	else
	{
		com->par_tail->next = newnode;
		com->par_tail = newnode;
	}
	return (true);
}

bool	line_to_par(t_com *com, char *line)
{
	if (*line)
		if (!add_par_node(com))
			return (false);
	while (*line)
	{
		line = trim_space(line);
		if (*line == '\'' || *line == '\"')
		{
			line = sq_qutes(line);
			continue ;
		}
		if (*line == '|')
			if (!add_par_node(com))
				return (false);
		++line;
	}
	return (true);
}

void	free_par_slist(t_par *par)
{
	t_snode	*node;

	while (par->head)
	{
		node = par->head;
		par->head = par->head->next;
		if (node->value)
			free(node->value);
		free(node);
	}
	par->head = NULL;
}
