/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:13:48 by maearly           #+#    #+#             */
/*   Updated: 2021/10/12 16:13:51 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//	line = readline(g_conf.prompt);

char	*readLine(void)
{
	char	*line;
	int		rl_catch_signals;

	rl_catch_signals = 0;
	rl_set_signals();
	defineInputSignals();
	line = readline("minishell $ ");
	rl_replace_line("", 0);
	if (line && *line)
		add_history (line);
	return (line);
}

//	TODO:	free(cmdLine);
void	mainLoop(char **env)
{
	char		*line;
	t_com		com;

	g_conf.com = &com;
	while (true)
	{
		line = readLine();
		if (line && line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!line)
		{
			if (isatty(0))
				write(2, "exit\n", 5);
			break ;
		}
		parser_ary(&com, line);
	}
}
