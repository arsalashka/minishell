/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 08:25:54 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:42:27 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static bool	add_pid(t_com *com, int pid)
{
	t_pid_node	*newnode;

	newnode = malloc(sizeof(t_pid_node));
	if (!newnode)
		return (false);
	newnode->pid = pid;
	newnode->next = NULL;
	if (!com->pw_list.head)
	{
		com->pw_list.head = newnode;
		com->pw_list.tail = newnode;
		return (true);
	}
	com->pw_list.tail->next = newnode;
	com->pw_list.tail = newnode;
	return (true);
}

static bool	extcute_duct(t_com *com, t_par *par)
{
	if (par->next && !par->next->in_node)
	{
		if (!wr_pipe(com, com->p))
		{
			if (com->p[0] == -1 && com->p[1] == 1)
				return (err_set(par, error_pipe));
			else
				return (err_set(par, error_malloc));
		}
		wr_close(com, com->p[1]);
		par->next->fd_in = com->p[0];
	}
	return (true);
}

static bool	child_proc(t_com *com, t_par *par)
{
	if (par->fd_in != 0 && dup2(par->fd_in, STDIN_FILENO) == -1)
		return (err_set(par, error_dupe));
	if (par->fd_out != 1 && dup2(par->fd_out, STDOUT_FILENO) == -1)
		return (err_set(par, error_dupe));
	close_inhereted(com, par->fd_in, par->fd_out);
	if (execve(par->path, par->argv, com->envp) == -1)
		return (err_set(par, error_execve));
	return (true);
}

bool	execute_par(t_com *com, t_par *par)
{
	if (!i_o_setup(com, par))
		return (false);
	g_conf.com->prev_ret = 0;
	par->pid = fork();
	defineExecSignals();
	if (par->pid < 0)
		return (err_set(par, error_fork));
	if (!par->pid)
	{
		if (!child_proc(com, par))
			return (false);
	}
	else
	{
		if (!add_pid(com, par->pid))
			return (err_set(par, error_malloc));
		if (par->fd_in != 0)
			wr_close(com, par->fd_in);
		if (par->fd_out != 1)
			wr_close(com, par->fd_out);
	}
	return (true);
}

bool	execute_pipeline(t_com *com, t_par *par)
{
	while (par)
	{
		if (par->error)
		{
			handleErrors(par, false, par->error);
			par = par->next;
			continue ;
		}
		if (!par->exe)
		{
			extcute_duct(com, par);
			par = par->next;
			continue ;
		}
		if (par->built_in)
			execBuiltin(par);
		else if (!execute_par(com, par))
		{
			par = par->next;
			continue ;
		}
		par = par->next;
	}
	return (true);
}
