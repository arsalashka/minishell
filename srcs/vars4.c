/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:51:13 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 18:51:15 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	predicate(void *s1, void *s2)
{
	const t_var	*ss1 = (const t_var *)s1;
	const t_var	*ss2 = (const t_var *)s2;

	return (ft_strcmp(ss1->key, ss2->key));
}

void	sorter(t_vect *this, int (*f)(void *, void *))
{
	int	i;
	int	j;
	int	size;

	i = -1;
	j = -1;
	size = (int) this->size;
	while (++i < (int) this->size)
	{
		while (++j < size - 1)
			if (f(at(this, j), at(this, j + 1)) > 0)
				swap(this, j, j + 1);
		size--;
		j = -1;
	}
}

void	swap(t_vect *this, int pos1, int pos2)
{
	void	*item;

	if (this == NULL)
		exit(1);
	if (pos1 >= this->size || pos2 >= this->size || pos1 == pos2)
		return ;
	item = this->data[pos1];
	this->data[pos1] = this->data[pos2];
	this->data[pos2] = item;
}

int	unsetVar(t_vect *env, char *key)
{
	int		index;
	t_var	*deleted_var;

	if (!key)
		return (1);
	if (!checkCharKey(key))
		return (pError("unset", key, "not a valid identifier", 1));
	index = indexOf(env, key, equalsKey);
	if (index == -1)
		return (0);
	deleted_var = (t_var *)removeAt(env, index);
	deleteVar(deleted_var);
	return (0);
}
