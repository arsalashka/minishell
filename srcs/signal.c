/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:56:45 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 20:56:47 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interruptProcess(int signal)
{
	(void)signal;
	g_conf.com->prev_ret = 130;
	write(1, "\n", 1);
}

static void	redisplayPrompt(int signal)
{
	(void)signal;
	g_conf.com->prev_ret = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	quitProcess(int signal)
{
	(void)signal;
	g_conf.com->prev_ret = 131;
	printf("Quit (core dumped)\n");
}

void	defineExecSignals(void)
{
	signal(SIGINT, interruptProcess);
	signal(SIGQUIT, quitProcess);
}

void	defineInputSignals(void)
{
	signal(SIGINT, redisplayPrompt);
	signal(SIGQUIT, SIG_IGN);
}
