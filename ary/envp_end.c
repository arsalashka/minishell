/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:49:57 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 12:38:50 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

static char	*remove_env(char *line, int place, int size, t_par *par)
{
	int		len;
	char	*newline;
	int		ct;

	chek_ambig(line, place, par);
	if (par->error == error_ambig)
	{
		if (!add_ambig_node(line, place, size, par))
			return (NULL);
		return (line);
	}
	len = ary_strlen(line) - size;
	newline = malloc(sizeof(char) * (len + 1));
	if (!newline)
		return (NULL);
	ct = -1;
	while (++ct < place)
		newline[ct] = line[ct];
	--ct;
	while (++ct < len)
		newline[ct] = line[size + ct];
	newline[ct] = '\0';
	free(line);
	return (newline);
}

static char	*rewrite_env(char *line, int place, char *env_val, int size)
{
	int		len;
	char	*newline;
	int		ct;
	int		val_len;
	int		i;

	val_len = ary_strlen(env_val);
	len = ary_strlen(line);
	newline = malloc(sizeof(char) * (len + val_len - size + 1));
	if (!newline)
		return (NULL);
	ct = -1;
	while (++ct < place)
		newline[ct] = line[ct];
	i = -1;
	while (++i < val_len)
		newline[ct++] = env_val[i];
	i = place + size;
	while (i < len)
		newline[ct++] = line[i++];
	newline[ct] = '\0';
	free(line);
	return (newline);
}

static void	fill_env(char *line, char *env, int size)
{
	int		ct;

	ct = -1;
	while (++ct < size)
		env[ct] = line[ct];
	env[ct] = '\0';
}

static int	size_of_envp(char *line)
{
	int		ct;

	ct = -1;
	if (*line == '-' || *line == '?' || *line == '*' || *line == '$'
		|| *line == '@' || *line == '_' || *line == '#' || *line == '!'
		|| (*line >= '0' && *line <= '9'))
		return (1);
	while (line[++ct])
		if (!(line[ct] > 64 && line[ct] < 91)
			&& !(line[ct] > 96 && line[ct] < 123))
			return (ct);
	return (ct);
}

char	*replace_envp(char *line, int place, int prev_ret, t_par *par)
{
	int		size;
	char	*env;
	char	*env_val;

	size = size_of_envp(line + place + 1);
	env = malloc(sizeof(char) * (size + 1));
	if (!env)
		return (NULL);
	fill_env(line + place + 1, env, size);
	if (ary_strcmp(env, "?"))
	{
		env_val = ft_itoa(prev_ret);
		if (!env_val)
			return (NULL);
		return (rewrite_env(line, place, env_val, size + 1));
	}
	env_val = getVar(g_conf.envp, env);
	free(env);
	if (!env_val)
		return (remove_env(line, place, size + 1, par));
	else
		return (rewrite_env(line, place, env_val, size + 1));
}
