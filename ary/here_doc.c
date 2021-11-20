/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:48:07 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 21:58:49 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	here_doc_input(t_com *com, char *limiter, t_par *par)
{
	char	buffer[512];
	int		ret;

	write(1, "heredoc> ", 9);
	while (true)
	{
		ret = read(STDIN_FILENO, buffer, 511);
		if (ret < 0)
			return (false);
		if (!ret)
		{
			write(1, "\n", 1);
			return (true);
		}
		buffer[ret - 1] = '\0';
		if (ary_strcmp(buffer, limiter))
			return (0);
		buffer[ret - 1] = '\n';
		buffer[ret] = '\0';
		write(com->p[1], buffer, ret);
		write(1, "heredoc> ", 9);
	}
}

static void	child(t_com *com, char *lim, t_par *par)
{
	wr_close(com, com->p[0]);
	signal(SIGINT, interruptHereDoc);
	here_doc_input(com, lim, par);
	wr_close(com, com->p[1]);
	exit(0);
}

static bool	here_doc_start(t_com *com, char *lim, t_par *par)
{
	int	pid;
	int	status;

	if (!wr_pipe(com, com->p))
		return (false);
	if (par->fd_hd)
		wr_close(com, par->fd_hd);
	par->fd_hd = com->p[0];
	pid = fork();
	if (pid < 0)
		return (err_set(par, error_fork));
	if (!pid)
		child(com, lim, par);
	else
	{
		defineExecSignals();
		wr_close(com, com->p[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			com->term = true;
			return (false);
		}
	}
	return (true);
}

bool	here_doc(t_com *com)
{
	t_par	*par;
	t_snode	*node;

	node = com->arg_start;
	par = com->par_head;
	com->term = false;
	node = com->arg_start;
	while (node)
	{
		if (ary_strcmp("|", node->value))
		{
			par = par->next;
			node = node->next;
		}
		if (ary_strcmp("<<", node->value))
		{
			if (!here_doc_start(com, node->next->value, par))
				return (false);
			par->heredoc = true;
			node = node->next;
			continue ;
		}
		node = node->next;
	}
	return (true);
}
