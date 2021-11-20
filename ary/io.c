/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:43:19 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:49:30 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static bool	pipe_duct(t_com *com, t_par *par)
{
	if (com->p[0] == -1 && com->p[1] == -1)
		return (err_set(par, error_pipe));
	else
		return (err_set(par, error_malloc));
	return (true);
}

static bool	i_o_pipework(t_com *com, t_par *par)
{
	if (par->next)
	{
		if (!wr_pipe(com, com->p))
		{
			if (!pipe_duct(com, par))
				return (false);
		}
		if (!par->out_node)
			par->fd_out = com->p[1];
		else
			wr_close(com, com->p[1]);
		par->next->fd_in = com->p[0];
	}
	if (par->heredoc)
		par->fd_in = par->fd_hd;
	return (true);
}

bool	i_o_setup(t_com *com, t_par *par)
{
	if (!i_o_pipework(com, par))
		return (false);
	else if (par->in_node)
	{
		par->fd_in = wr_open(com, par->in_node->value, O_RDONLY);
		if (par->fd_in == -1)
			return (err_set(par, error_open));
		if (par->fd_in == -2)
			return (err_set(par, error_malloc));
	}
	if (par->out_node)
	{
		if (par->append)
			par->fd_out = wr_open(com, par->out_node->value,
					O_WRONLY | O_APPEND);
		else
			par->fd_out = wr_open(com, par->out_node->value,
					O_WRONLY | O_TRUNC);
		if (par->fd_out == -1)
			return (err_set(par, error_open));
		if (par->fd_out == -2)
			return (err_set(par, error_malloc));
	}
	return (true);
}

static void	setup_out_add(t_com *com, t_snode *node, t_par *par)
{
	if (access(node->value, F_OK))
	{
		if (!make_file(node->value) && !par->error)
		{
			par->error = error_create;
			par->error_node = node;
		}
	}
	else if (access(node->value, W_OK))
	{
		if (!par->error)
		{
			par->error = error_noprem;
			par->error_node = node;
		}
	}
}

void	setup_out(t_com *com, t_snode *node, t_par *par)
{
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			node = node->next;
			par = par->next;
		}
		if (par && (par->input_err || par->error == error_ambig))
		{
			node = skip_par(node);
			continue ;
		}
		if ((ary_strcmp(">>", node->value) || ary_strcmp(">", node->value)))
		{
			node = node->next;
			setup_out_add(com, node, par);
			continue ;
		}
		node = node->next;
	}
}
