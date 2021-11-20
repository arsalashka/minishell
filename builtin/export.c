/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:16:29 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 18:16:32 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

extern t_shell	g_conf;

static int	printVar(t_var *var, int fd)
{
	int	i;

	i = -1;
	write(fd, "declare -x ", 11);
	write(fd, var->key, strlen(var->key));
	if (var->value)
	{
		write(fd, "=\"", 2);
		while (var->value[++i])
		{
			if (var->value[i] == '$')
				write(fd, "\\", 1);
			write(fd, &var->value[i], 1);
		}
		write(fd, "\"", 1);
	}
	write(fd, "\n", 1);
	return (0);
}

static int	export_vars(int ac, char **av)
{
	int	i;
	int	code;

	i = 0;
	code = 0;
	while (++i < ac)
	{
		if (setVar(g_conf.envp, av[i]) != 0)
			code = 1;
	}
	return (code);
}

int	export(int ac, char **av, int fd)
{
	g_conf.com->prev_ret = 0;
	if (ac == 1)
		listVars(g_conf.envp, true, printVar, fd);
	else if (ac > 1)
		return (export_vars(ac, av));
	return (0);
}
