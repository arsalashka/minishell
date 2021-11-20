/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:06:23 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:35:41 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**list_to_char(t_argv_list *list, char *head)
{
	char	**ret;
	int		ct;
	t_snode	*temp;

	ret = malloc(sizeof(char *) * (++list->size + 1));
	if (!ret)
		return (NULL);
	ret[list->size] = NULL;
	ret[0] = head;
	ct = 0;
	while (++ct < list->size)
	{
		temp = list->head;
		ret[ct] = temp->value;
		list->head = list->head->next;
		free(temp);
	}
	list->size = 0;
	list->head = NULL;
	return (ret);
}

static bool	argv_duct(t_par *par, t_argv_list *list)
{
	par->argv = list_to_char(list, par->exe->value);
	if (!par->argv)
		return (false);
	return (true);
}

static bool	add_to_argv_list(t_argv_list *list, void *val)
{
	t_snode	*newnode;

	newnode = malloc(sizeof(t_snode));
	if (!newnode)
		return (NULL);
	newnode->value = val;
	newnode->next = NULL;
	if (!list->head)
	{
		list->head = newnode;
		list->tail = newnode;
		++list->size;
		return (true);
	}
	list->tail->next = newnode;
	list->tail = newnode;
	++list->size;
	return (true);
}

bool	setup_argv(t_com *com, t_snode *node, t_par *par, t_argv_list *list)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			node = node->next;
			if (par->exe && !argv_duct(par, list))
				return (false);
			par = par->next;
		}
		if (par && par->error)
		{
			node = skip_par(node);
			continue ;
		}
		if (par && prev_chek(node->prev))
			if (node != par->exe && !is_com_sym(node->value))
				if (!add_to_argv_list(list, node->value))
					return (false);
		node = node->next;
	}
	if (par && par->exe && !argv_duct(par, list))
		return (false);
	return (true);
}
