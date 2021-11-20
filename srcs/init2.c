/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:45:56 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 20:45:57 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	updateShlvl(void)
{
	int		value;
	t_var	*var;
	char	*value_str;

	var = getVar2(g_conf.envp, "SHLVL");
	value = 0;
	if (var != NULL)
		if (var->value != NULL)
			value = ft_atoi(var->value);
	value++;
	if (value == 1000)
		value_str = ft_strdup("");
	else if (value > 1000 || value < 0)
	{
		if (value == 1001)
			pError("warning", NULL,
				   "shell level (1001) too high, resetting to 1", 1);
		value_str = ft_itoa(1);
	}
	else
		value_str = ft_itoa(value);
	setVar2(g_conf.envp, "SHLVL", value_str, true);
	free(value_str);
	return (0);
}

char	**extractEnvp(t_vect *g_env)
{
	t_var	*var;
	char	**envp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	envp = (char **)ft_malloc((g_env->size + 1) * sizeof(char *));
	while (++i < (int) g_env->size)
	{
		var = (t_var *)at(g_env, i);
		if (var->value != NULL)
			envp[j++] = var->raw;
	}
	envp[j] = NULL;
	return (envp);
}
