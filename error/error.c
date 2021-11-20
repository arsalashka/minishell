/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:16:32 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 19:16:33 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	syntaxError(char *arg, char *arg2, char *message, int code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	if (arg)
		write(2, arg, ft_strlen(arg));
	if (arg2)
	{
		write(2, arg2, ft_strlen(arg2));
		write(2, ": ", 2);
	}
	if (message)
	{
		write(2, "`", 1);
		write(2, message, ft_strlen(message));
		write(2, "'", 1);
	}
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	return (false);
}

int	pError(char *arg, char *arg2, char *message, int code)
{
	write(2, "minishell: ", ft_strlen("minishell: "));
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (arg2)
	{
		write(2, arg2, ft_strlen(arg2));
		write(2, ": ", 2);
	}
	if (message)
		write(2, message, ft_strlen(message));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
	g_conf.com->prev_ret = code;
	return (code);
}

void	handleErrors(t_par *par, bool ispath, int errno_)
{
	struct stat	dir_stat;

	if (ispath && stat(par->argv[0], &dir_stat) == 0
		&& S_ISDIR(dir_stat.st_mode))
		pError(par->argv[0], NULL, "is a directory", 126);
	else if (errno_ == -13)
		exit(pError(NULL, NULL, "Malloc error", 1));
	else if (errno_ == -4)
		exit(pError(NULL, NULL, "Waitpid error", 1));
	else if (errno_ == 8)
		exit(pError(par->argv[0], NULL, NULL, 1));
	else if (errno_ == -10)
		pError((char *)par->error_node->value, NULL,
			   "Permission denied", 1);
	else if (errno_ == 13)
		pError(par->argv[0], NULL, NULL, 126);
	else if (errno_ == -11)
		pError((char *)par->argv[0], NULL,
			   "No such file or directory", 1);
	else if (ispath || getVar(g_conf.envp, "PATH") == NULL)
		pError(par->argv[0], NULL, NULL, 127);
	else
		pError(par->argv[0], NULL,
			   "command not found", 127);
}
