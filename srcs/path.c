/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:10:24 by maearly           #+#    #+#             */
/*   Updated: 2021/10/22 18:10:25 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*appendCmdToPath(char *path, char *cmd)
{
	int			i;
	int			j;
	char		*out;
	const int	len = ft_strlen(path) + ft_strlen(cmd) + 2;

	i = 0;
	j = 0;
	out = (char *)ft_malloc(len * sizeof(char));
	while (path[i])
		out[j++] = path[i++];
	out[j++] = '/';
	i = 0;
	while (cmd[i])
		out[j++] = cmd[i++];
	out[j] = '\0';
	free(path);
	return (out);
}

char	*getPath(char *path_str, char *cmd, int *start, int end)
{
	char	*path;

	path = ft_substr(path_str, *start, end - *start);
	if (path != NULL)
		path = appendCmdToPath(path, cmd);
	else
		path = appendCmdToPath(ft_strdup("."), cmd);
	*start = end + 1;
	return (path);
}

t_vect	*getPathes(char *path_str, char *cmd)
{
	t_vect	*pathes;
	int		end;
	int		start;

	end = -1;
	start = 0;
	pathes = newVector(30);
	if (!pathes)
		exit(1);
	if (path_str != NULL && path_str[0] != '\0')
	{
		while (path_str[++end])
			if (path_str[end] == ':')
				insert(pathes, getPath(path_str, cmd, &start, end));
		insert(pathes, getPath(path_str, cmd, &start, end));
	}
	else
		insert(pathes, appendCmdToPath(ft_strdup("."), cmd));
	return (pathes);
}
