/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inhereted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:43:34 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:43:35 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/* makes node for inhereted list */

static t_inh_node	*get_inh_node(int fd)
{
	t_inh_node	*newnode;

	newnode = malloc(sizeof(t_inh_node));
	if (!newnode)
		return (NULL);
	newnode->next = NULL;
	newnode->fd = fd;
	return (newnode);
}

/* adds node with stored fd in inhreted list */

bool	add_to_inh_list(t_inh_list *list, int fd)
{
	t_inh_node	*newnode;

	newnode = get_inh_node(fd);
	if (!newnode)
		return (false);
	if (!list->head)
	{
		list->head = newnode;
		list->tail = newnode;
	}
	else
	{
		list->tail->next = newnode;
		list->tail = newnode;
	}
	return (true);
}

/*	closes all fd in inhereted list */

void	close_inhereted(t_com *cmd, int in, int out)
{
	t_inh_node	*node;

	if (in != 0)
		wr_close(cmd, in);
	if (out != 1)
		wr_close(cmd, out);
	node = cmd->inh_list.head;
	while (node)
	{
		if (node->fd != in && node->fd != out)
			close(node->fd);
		node = node->next;
	}
	cmd->inh_list.head = NULL;
}
