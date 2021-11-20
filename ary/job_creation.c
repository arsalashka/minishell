/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 07:00:07 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 21:06:00 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static void	check_in(t_com *com, t_snode *node, t_par *par)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			node = node->next;
			par = par->next;
		}
		if (ary_strcmp("<", node->value))
		{
			node = node->next;
			if (access(node->value, F_OK))
				par->error = error_nofile;
			else if (access(node->value, R_OK))
				par->error = error_noprem;
			if (par->error)
			{
				par->input_err = true;
				par->error_node = node;
			}
			node = skip_par(node);
			continue ;
		}
		node = node->next;
	}
}

static void	setup_par(t_com *com)
{
	t_par	*par;
	t_snode	*node;

	node = com->arg_start;
	par = com->par_head;
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			node = node->next;
			par = par->next;
		}
		if (par && par->error)
		{
			node = skip_par(node);
			continue ;
		}
		find_last_in(node, par);
		find_last_out(node, par);
		node = skip_par(node);
	}
}

static void	setup_exe(t_com *com, t_snode *node, t_par *par)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			node = node->next;
			par = par->next;
		}
		if (par && par->error)
		{
			node = skip_par(node);
			continue ;
		}
		if (par && prev_chek(node->prev) && node->value
			&& !is_com_node(node->value))
		{
			par->exe = node;
			node = skip_par(node);
			continue ;
		}
		node = node->next;
	}
}

bool	reform_nodes(t_com *com)
{
	int			size;
	int			ct;
	t_argv_list	list;

	list.head = NULL;
	list.size = 0;
	size = 0;
	if (!here_doc(com))
		return (false);
	check_in(com, com->arg_start, com->par_head);
	setup_out(com, com->arg_start, com->par_head);
	setup_par(com);
	setup_exe(com, com->arg_start, com->par_head);
	if (!setup_path(com, com->par_head))
		handleErrors(com->par_head, false, error_malloc);
	if (!setup_argv(com, com->arg_start, com->par_head, &list))
		handleErrors(com->par_head, false, error_malloc);
	return (true);
}
