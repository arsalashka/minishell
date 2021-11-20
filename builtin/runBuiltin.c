/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runBuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 16:25:14 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 16:25:17 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	isBuiltin(char *str)
{
	return (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "env") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "cd") == 0);
}

int	execBuiltin(t_par *par)
{
	if (ft_strcmp(par->argv[0], "cd") == 0)
		return (cd(count_args(par->argv), par->argv, par->fd_out));
	else if (ft_strcmp(par->argv[0], "echo") == 0)
		return (echo(count_args(par->argv), par->argv, par->fd_out));
	else if (ft_strcmp(par->argv[0], "export") == 0)
		return (export(count_args(par->argv), par->argv, par->fd_out));
	else if (ft_strcmp(par->argv[0], "env") == 0)
		return (env(par->fd_out));
	else if (ft_strcmp(par->argv[0], "exit") == 0)
		return (ft_exit(count_args(par->argv), par->argv));
	else if (ft_strcmp(par->argv[0], "pwd") == 0)
		return (pwd(par->fd_out));
	else if (ft_strcmp(par->argv[0], "unset") == 0)
		return (unset(count_args(par->argv), par->argv));
	return (1);
}
