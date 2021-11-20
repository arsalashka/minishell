/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:28:05 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:56:34 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	add_snode(t_com *com, char *line)
{
	t_snode		*newnode;

	newnode = malloc(sizeof(t_snode));
	if (!newnode)
	{
		free(line);
		return (false);
	}
	newnode->value = line;
	if (!com->arg_start)
	{
		newnode->next = NULL;
		newnode->prev = NULL;
		com->arg_start = newnode;
		com->arg_last = newnode;
		return (true);
	}
	newnode->prev = com->arg_last;
	com->arg_last->next = newnode;
	newnode->next = NULL;
	com->arg_last = newnode;
	return (true);
}

void	free_snode(t_snode *head)
{
	t_snode	*temp;

	while (head)
	{
		temp = head;
		free(temp->value);
		head = head->next;
		free(temp);
	}
}

bool	add_ambig_node(char *line, int place, int size, t_par *par)
{
	char	*newline;
	t_snode	*newnode;
	int		ct;

	newline = malloc(sizeof(char) * (size + 1));
	if (!newline)
		return (false);
	ct = -1;
	while (++ct < size)
		newline[ct] = line[place + ct];
	newline[ct] = '\0';
	newnode = malloc(sizeof(t_snode));
	if (!newnode)
	{
		free(newline);
		return (false);
	}
	newnode->value = newline;
	par->error_node = newnode;
	return (true);
}
