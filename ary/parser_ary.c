/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:11:45 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 21:51:41 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**listToArgv(t_com *com)
{
	char	**tmp;
	int		i;
	t_snode	*head;

	tmp = ft_malloc(sizeof(char *) * (com->ac + 1));
	head = com->arg_start;
	i = -1;
	while (++i < com->ac)
	{
		tmp[i] = (char *)head->value;
		head = head->next;
	}
	tmp[i] = NULL;
	return (tmp);
}

int	count_args(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

void	com_init(t_com *com)
{
	com->arg_start = NULL;
	com->pw_list.head = NULL;
	com->inh_list.head = NULL;
	com->par_head = NULL;
	com->syntax = 0;
}

bool	checkSome(t_com *com, char *line)
{
	if (!line || !*line)
		return (false);
	if (empty_line(line))
		return (false);
	if (!syntax_err(com, line))
		return (syntaxError("syntax error near unexpected token ",
				NULL, line, 258));
	return (true);
}

int	parser_ary(t_com *com, char *line)
{
	com_init(com);
	com->envp = extractEnvp(g_conf.envp);
	com->ac = countArgc(com);
	com->av = listToArgv(com);
	if (!checkSome(com, line))
		return (0);
	if (!line_to_par(com, line))
		handleErrors(NULL, false, error_malloc);
	if (!split_line_to_pars(com, line))
		handleErrors(NULL, false, error_malloc);
	if (!par_envp(com))
		handleErrors(NULL, false, error_malloc);
	free(line);
	par_to_parse(com);
	if (!reform_nodes(com) && com->term)
	{
		free_all(com, com->par_head);
		return (0);
	}
	execute_pipeline(com, com->par_head);
	wait_all_pids(com);
	close_inhereted(com, 0, 1);
	free_all(com, com->par_head);
	return (0);
}
