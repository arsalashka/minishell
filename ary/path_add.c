/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:09:56 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:17:53 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
#include "../includes/minishell.h"

bool	tape_it(int ct, char **paths, char *name, char **path)
{
	char	*temp;

	temp = paths[ct];
	paths[ct] = ft_strjoin(paths[ct], "/");
	if (!paths[ct])
		return (false);
	free(temp);
	*path = ft_strjoin(paths[ct], name);
	if (!path)
		return (false);
	return (true);
}
