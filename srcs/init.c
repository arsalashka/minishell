/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:05:39 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 17:05:41 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	addCurrEnv(t_vect *envp, void *current)
{
	void	**old;
	size_t	capacity;
	int		i;

	if (envp == NULL)
		exit (1);
	if (envp->size == envp->capacity - 1)
	{
		capacity = envp->capacity + envp->capacity / 2;
		old = (void **) ft_malloc(sizeof(void *) * capacity);
		i = -1;
		while (++i < (int)envp->size)
			old[i] = envp->data[i];
		free(envp->data);
		envp->data = old;
		envp->capacity = capacity;
	}
	envp->data[envp->size++] = current;
	envp->data[envp->size] = NULL;
}

int	unSetVar(t_vect *envp, char *str)
{
	t_var	*delVar;
	int		index;

	if (!str)
		return (1);
	if (!checkCharKey(str))
		return (pError("unset", str, "not a valid identifire", 1));
	index = indexOf(envp, str, equalsKey);
	if (index == -1)
		return (0);
	delVar = (t_var *)removeAt(envp, index);
	deleteVar(delVar);
	return (0);
}

int	setEnvp(char **env)
{
	int	i;

	if (!env)
		return (1);
	g_conf.envp = newVect();
	i = -1;
	while (env[++i] != NULL)
		addCurrEnv(g_conf.envp, newVarS(env[i]));
	unSetVar(g_conf.envp, "OLDPWD");
	updateShlvl();
	return (0);
}

void	initializate(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_conf.forked = false;
	setEnvp(env);
	g_conf.prompt = ft_strjoin(getVar(g_conf.envp, "PWD"), " $ ");
	g_conf.com = NULL;
}
