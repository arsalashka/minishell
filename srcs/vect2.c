/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:35:45 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 20:35:46 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*search(t_vect *this, void *item, bool (*eqlKey)(void *, void *))
{
	int	i;

	if (this == NULL)
		exit(1);
	i = -1;
	while (++i < (int) this->size)
	{
		if (eqlKey(this->data[i], item))
			return (this->data[i]);
	}
	return (NULL);
}

void	insert(t_vect *envp, void *var)
{
	void	**old_data;
	size_t	new_capacity;
	int		i;

	if (envp == NULL)
		exit(1);
	if (envp->size == envp->capacity - 1)
	{
		i = -1;
		new_capacity = envp->capacity + envp->capacity / 2;
		old_data = (void **)ft_malloc(sizeof(void *) * new_capacity);
		while (++i < (int)envp->size)
			old_data[i] = envp->data[i];
		free(envp->data);
		envp->data = old_data;
		envp->capacity = new_capacity;
	}
	envp->data[envp->size++] = var;
	envp->data[envp->size] = NULL;
}

t_vect	*newVectorFrom(t_vect *other)
{
	int		i;
	size_t	length;
	t_vect	*new;

	if (other == NULL || is_empty(other))
		exit(1);
	length = other->size + other->size / 2;
	new = newVector(length);
	i = -1;
	while (++i < other->size)
		new->data[new->size++] = other->data[i];
	return (new);
}

void	delete(t_vect *vect)
{
	if (vect == NULL)
		return ;
	if (vect->data != NULL)
		free(vect->data);
	vect->data = NULL;
	free(vect);
	vect = NULL;
}

void	deleteFree(t_vect *this, void (*f)(void *))
{
	if (!this)
		return ;
	if (this->data != NULL)
	{
		while (!is_empty(this))
			f(removeAt(this, this->size - 1));
		free(this->data);
		this->data = NULL;
	}
	free(this);
	this = NULL;
}
