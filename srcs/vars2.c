/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:44:10 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 19:44:12 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	checkKey(t_var *var)
{
	int		i;
	char	c;

	if (!var || !var->key)
		return (false);
	i = 0;
	c = var->key[i];
	if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
		return (false);
	while (var->key[++i])
	{
		c = var->key[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
				 	 || (c >= '0' && c <= '9') || (c == '_')))
			return (false);
	}
	return (true);
}

void	deleteVar(void *var)
{
	t_var	*v;

	v = (t_var *)var;
	if (!v)
		return ;
	if (v->key)
		free(v->key);
	if (v->raw)
		free(v->raw);
	if (v->value)
		free(v->value);
	free(v);
}

t_var	*newVarKV(char *key, char *value)
{
	int		i;
	int		j;
	t_var	*var;

	var = (t_var *)ft_malloc(sizeof(t_var));
	var->raw = (char *)ft_malloc((strlen(key) + strlen(value) + 2)
			 * sizeof(char));
	bzero(var->raw, (strlen(key) + strlen(value) + 2));
	var->key = key;
	var->value = value;
	i = -1;
	j = 0;
	while (key[++i])
		var->raw[j++] = key[i];
	var->raw[j++] = '=';
	i = -1;
	while (value[++i])
		var->raw[j++] = value[i];
	var->raw[j] = '\0';
	return (var);
}

int	updateVar(t_var *var, t_var *new)
{
	if (var->value != NULL)
		free(var->value);
	free(var->key);
	free(var->raw);
	var->value = new->value;
	var->key = new->key;
	var->raw = new->raw;
	free(new);
	return (0);
}

int	setVar2(t_vect *env, char *key, char *value, bool check)
{
	t_var	*var;
	t_var	*existing_var;

	var = newVarKV(ft_strdup(key), ft_strdup(value));
	if (check && !checkKey(var))
	{
		deleteVar(var);
		return (pError("export", key, "not a valid identifier", 1));
	}
	existing_var = search(env, var->key, equalsKey);
	if (!existing_var)
		insert(env, var);
	else if (var->value)
		updateVar(existing_var, var);
	else
		deleteVar(var);
	return (0);
}
