/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:35:52 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 19:35:53 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

extern t_shell	g_conf;

int	unset(int ac, char **av)
{
	int		i;
	int		code;

	g_conf.com->prev_ret = 0;
	if (ac == 1)
		return (0);
	i = 0;
	code = 0;
	while (av[++i])
		if (unsetVar(g_conf.envp, av[i]) != 0)
			code = 1;
	return (code);
}
