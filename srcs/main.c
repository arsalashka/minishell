/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:53:01 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 16:53:03 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	g_conf;

void	interruptHereDoc(int signal)
{
	(void)signal;
	g_conf.com->prev_ret = 130;
	exit(130);
}

int	main(int ac, char **av, char **env)
{
	initializate(ac, av, env);
	mainLoop(env);
	return (EXIT_SUCCESS);
}
