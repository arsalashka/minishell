/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:39:09 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 18:39:11 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vect	*newVector(size_t size)
{
	t_vect	*new;

	new = (t_vect *)ft_malloc(sizeof(t_vect));
	new->data = (void **)ft_malloc(sizeof(void *) * size);
	new->capacity = size;
	new->size = 0;
	return (new);
}

int	indexOf(t_vect *envp, void *str, bool (*eqlKey)(void *, void *))
{
	int	i;

	if (envp == NULL)
		exit(1);
	i = -1;
	while (++i < (int)envp->size)
	{
		if (eqlKey(envp->data[i], str))
			return (i);
	}
	return (-1);
}

int	is_empty(t_vect *envp)
{
	if (envp == NULL)
		exit(1);
	return (envp->size == 0);
}

void	*at(t_vect *envp, int pos)
{
	if (envp == NULL)
		exit(1);
	if (pos >= envp->size)
		exit(1);
	return (envp->data[pos]);
}

void	*removeAt(t_vect *envp, int pos)
{
	int		i;
	void	*item;

	if (envp == NULL)
		exit(EXIT_FAILURE);
	if (is_empty(envp))
		return (NULL);
	if (pos >= envp->size)
		return (NULL);
	i = pos;
	item = at(envp, pos);
	while (i < (int) envp->size)
	{
		if (i + 1 < (int) envp->size)
			envp->data[i] = envp->data[i + 1];
		i++;
	}
	envp->size--;
	envp->data[envp->size] = NULL;
	return (item);
}
