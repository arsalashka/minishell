/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:46:30 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 20:46:31 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getVar(t_vect *env, char *key)
{
	t_var	*var;

	var = search(env, key, equalsKey);
	if (!var)
		return (NULL);
	return (var->value);
}

t_var	*getVar2(t_vect *env, char *key)
{
	t_var	*var;

	var = search(env, key, equalsKey);
	return (var);
}

int	setVar(t_vect *env, char *var_str)
{
	t_var	*var;
	t_var	*existing_var;

	var = newVarS(var_str);
	if (!checkKey(var))
	{
		free(var->key);
		free(var->raw);
		if (var->value)
			free(var->value);
		g_conf.com->prev_ret = 2;
		return (pError("export", var_str, "not a valid identifier", 1));
	}
	existing_var = search(env, var->key, equalsKey);
	if (!existing_var)
		insert(env, var);
	else if (var->value)
		updateVar(existing_var, var);
	else
	{
		free(var->key);
		free(var->raw);
		free(var);
	}
	return (0);
}

int	printVar2(t_var *var, int fd)
{
	fd = 0;
	if (var->value)
	{
		write(1, var->raw, strlen(var->raw));
		write(1, "\n", 1);
	}
	return (0);
}

int	listVars(t_vect *env, bool sort, int (*print)(t_var *, int), int fd)
{
	t_vect	*vector;
	t_var	*var;
	int		i;

	i = -1;
	vector = newVectorFrom(env);
	if (sort)
		sorter(vector, predicate);
	while (++i < (int)env->size)
	{
		var = (t_var *)at(vector, i);
		if (ft_strcmp(var->key, "?") != 0)
			print(var, fd);
	}
	delete(vector);
	return (0);
}
