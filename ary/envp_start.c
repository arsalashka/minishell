/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:04:35 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:39:35 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	count_envp(char *line)
{
	int		ret;
	char	*base;

	base = line;
	ret = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			line = quote_skip(line);
			continue ;
		}
		if (*line == '$' && chek_back(line, base) && chek_line(line[1]))
			++ret;
		++line;
	}
	return (ret);
}

char	*envp_proc(char *line, int prev_ret, t_par *par)
{
	int		ct;

	ct = 0;
	while (line[ct])
	{
		if (line[ct] == '\'')
		{
			ct += alt_quote_skip(line + ct);
			continue ;
		}
		if (line[ct] == '$' && chek_back(line + ct, line)
			&& chek_line(line[ct + 1]))
			return (replace_envp(line, ct, prev_ret, par));
		++ct;
	}
	return (line);
}

bool	par_envp(t_com *com)
{
	t_par	*par;
	int		ct;
	int		envc;

	par = com->par_head;
	while (par)
	{
		envc = count_envp(par->line);
		ct = -1;
		while (++ct < envc)
		{
			par->line = envp_proc(par->line, com->prev_ret, par);
			if (!par->line)
				return (false);
			if (chek_empty(par->line))
			{
				free(par->line);
				par->line = NULL;
			}
		}
		par = par->next;
	}
	return (true);
}
