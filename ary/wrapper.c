/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:48:03 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 20:58:17 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/* wrapped open - it automaticly adds opend fd in inhereted list */

int	wr_open(t_com *cmd, char *name, int mode)
{
	int	fd;

	fd = open(name, mode);
	if (fd < 0)
		return (-1);
	if (!(add_to_inh_list(&cmd->inh_list, fd)))
		return (-2);
	return (fd);
}

/* wrapped pipe - it automaticly adds opend fds in inhereted list */

bool	wr_pipe(t_com *cmd, int *p)
{
	if (pipe(p))
	{
		p[0] = -1;
		p[1] = -1;
		return (false);
	}
	if (!(add_to_inh_list(&cmd->inh_list, p[0])))
	{
		close(p[0]);
		close(p[1]);
		return (false);
	}
	if (!(add_to_inh_list(&cmd->inh_list, p[1])))
	{
		wr_close(cmd, p[0]);
		close(p[1]);
		return (false);
	}
	return (true);
}

/* wrapped close - it automaticly removes fd's from inhereted list */

bool	wr_close(t_com *cmd, int fd)
{
	t_inh_node	*node;
	t_inh_node	*node_prew;

	node = cmd->inh_list.head;
	node_prew = NULL;
	while (node)
	{
		if (node->fd == fd)
		{
			if (node_prew)
			{
				node_prew->next = node->next;
				if (node == cmd->inh_list.tail)
					cmd->inh_list.tail = node_prew;
			}
			else
				cmd->inh_list.head = cmd->inh_list.head->next;
			close(fd);
			free(node);
			return (true);
		}
		node_prew = node;
		node = node->next;
	}
	return (false);
}
