/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:38:16 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 18:38:17 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	charOfStr(const char *str, char c)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

t_var	*newVarV(char *key, char *value, char *raw)
{
	t_var	*var;

	var = (t_var *)ft_malloc(sizeof(t_var));
	var->key = key;
	var->value = value;
	var->raw = raw;
	return (var);
}

t_var	*newVarS(char *var_str)
{
	int		index_of_eq;
	char	*value;

	index_of_eq = charOfStr(var_str, '=');
	if (index_of_eq == -1)
		return (newVarV(ft_strdup(var_str), NULL, ft_strdup(var_str)));
	value = ft_substr(var_str, index_of_eq + 1, ft_strlen(var_str));
	if (!value)
		value = ft_strdup("");
	return (newVarV(ft_substr(var_str, 0, index_of_eq), value,
			ft_strdup(var_str)));
}

bool	checkCharKey(char *key)
{
	int		i;
	char	c;

	if (!key)
		return (false);
	i = 0;
	c = key[i];
	if (!(ft_isalpha(c) || (c == '_')))
		return (false);
	while (key[++i])
	{
		c = key[i];
		if (!(ft_isalnum(c) || (c == '_')))
			return (false);
	}
	return (true);
}

bool	equalsKey(void *item1, void *item2)
{
	const t_var	*var1 = (t_var *)item1;
	const char	*var2_key = (char *)item2;

	return (strcmp(var1->key, var2_key) == 0);
}
