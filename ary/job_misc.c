/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 07:15:44 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:51:41 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	find_last_in(t_snode *node, t_par *par)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
			return ;
		if (ary_strcmp("<", node->value))
		{
			node = node->next;
			par->in_node = node;
			par->heredoc = false;
			continue ;
		}
		if (ary_strcmp("<<", node->value))
		{
			node = node->next;
			par->heredoc = true;
			par->in_node = NULL;
			continue ;
		}
		node = node->next;
	}
}

void	find_last_out(t_snode *node, t_par *par)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
			return ;
		if (ary_strcmp(">", node->value))
		{
			node = node->next;
			par->append = false;
			par->out_node = node;
			continue ;
		}
		if (ary_strcmp(">>", node->value))
		{
			node = node->next;
			par->append = true;
			par->out_node = node;
			continue ;
		}
		node = node->next;
	}
}

bool	prev_chek(t_snode *node)
{
	if (!node || ary_strcmp("|", node->value))
		return (true);
	if (ary_strcmp("<<", node->value) || ary_strcmp("<", node->value)
		|| ary_strcmp(">>", node->value) || ary_strcmp(">", node->value))
		return (false);
	return (true);
}

bool	is_com_node(char *line)
{
	if (ary_strcmp("|", line))
		return (true);
	if (ary_strcmp(">>", line))
		return (true);
	if (ary_strcmp(">", line))
		return (true);
	if (ary_strcmp("<<", line))
		return (true);
	if (ary_strcmp("<", line))
		return (true);
	return (false);
}
