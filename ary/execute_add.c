/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:49:51 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:40:38 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

bool	wait_all_pids(t_com *com)
{
	t_pid_node	*node;
	int			status;

	while (com->pw_list.head)
	{
		node = com->pw_list.head;
		if (waitpid(node->pid, &status, 0) == -1)
			return (false);
		if (WIFEXITED(status))
			com->prev_ret = WEXITSTATUS(status);
		com->pw_list.head = com->pw_list.head->next;
		free(node);
	}
	return (true);
}
