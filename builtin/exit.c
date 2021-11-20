/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:19:12 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 19:19:13 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

void	freeAll(char **all)
{
	int		i;

	if (!all)
		return ;
	i = -1;
	while (all[++i])
		free(all[i]);
	free(all);
}

bool	ft_isdigits(char *val)
{
	int		i;

	i = 0;
	if (!val || !val[0])
		return (false);
	if (val[i] == '-')
		i++;
	while (val[i])
		if (!ft_isdigit(val[i++]))
			return (false);
	return (true);
}

bool	check_value(char *val)
{
	bool		code;
	char		**vals;

	code = true;
	if (!val || !val[0])
		return (false);
	vals = ft_split(val, ' ');
	if (vals[1] != NULL || !ft_isdigits(vals[0]))
		code = pError("exit", val, "numeric argument required", false);
	else if (vals[0][0] != '-' && ft_strlen(vals[0]) == 19)
	{
		if (ft_strcmp(vals[0], MAXVAL) > 0)
			code = pError("exit", val, "numeric argument required", false);
	}
	else if (vals[0][0] == '-' && ft_strlen(vals[0]) == 20)
	{
		if (ft_strcmp(vals[0], MINVAL) > 0)
			code = pError("exit", val, "numeric argument required", false);
	}
	else if ((vals[0][0] != '-' && ft_strlen(vals[0]) > 19)
			 || (vals[0][0] == '-' && ft_strlen(vals[0]) > 20))
		code = pError("exit", val, "numeric argument required", false);
	freeAll(vals);
	return (code);
}

int	ft_exit(int ac, char **av)
{
	unsigned char	code;

	if (!g_conf.forked)
		write(1, "exit\n", 5);
	if (ac < 2)
		exit(0);
	if (!check_value(av[1]))
		exit(255);
	code = (unsigned char)ft_atol(av[1]);
	if (ac > 2)
		return (pError("exit", NULL, "too many arguments", 1));
	deleteFree(g_conf.envp, &deleteVar);
	free(g_conf.prompt);
	exit(code);
}
