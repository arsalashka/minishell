/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 07:23:26 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:13:23 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static char	*envp_parse(char **envp)
{
	int	ct;

	ct = -1;
	while (envp[++ct])
		if (ary_strlen(envp[ct]) > 5 && envp[ct][0] == 'P'
			&& envp[ct][1] == 'A' && envp[ct][2] == 'T'
			&& envp[ct][3] == 'H' && envp[ct][4] == '=')
			break ;
	return (envp[ct]);
}

static char	*find_path(t_par *par, char **paths, char *name, int ct)
{
	char	*path;

	while (paths[++ct])
	{
		if (!tape_it(ct, paths, name, &path))
			return (NULL);
		if (!(access(path, F_OK)))
		{
			if (!(access(path, X_OK)))
			{
				par->error = 0;
				return (path);
			}
			par->error = error_noprem;
		}
		free(path);
	}
	par->error_node = par->exe;
	par->error = error_nocom;
	return (NULL);
}

static bool	pathsfinder(t_com *com, t_par *par)
{
	char	*env_path;
	char	**paths;

	env_path = envp_parse(com->envp);
	if (!env_path)
		par->error = error_nofile;
	else
	{
		paths = ft_split(env_path + 5, ':');
		if (!paths)
			return (false);
		par->path = find_path(par, paths, par->exe->value, -1);
		if (!par->path && par->error != error_nocom)
			return (false);
	}
	return (true);
}

static bool	path_duct(t_par *par)
{
	par->path = ary_strdup(par->exe->value);
	if (!par->path)
		return (false);
	return (true);
}

bool	setup_path(t_com *com, t_par *par)
{
	while (par)
	{
		par->built_in = isBuiltin((char *)par->exe->value);
		if (par->exe && !par->built_in)
		{
			if (!par->error && !access(par->exe->value, F_OK))
			{
				if (access(par->exe->value, X_OK))
				{
					par->error = error_noprem;
					continue ;
				}
				else if (!path_duct(par))
					return (false);
			}
			else if (!pathsfinder(com, par))
				return (false);
		}
		par = par->next;
	}
	return (true);
}
