/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:06:00 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 17:06:02 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

static void	writeBackslashN(bool new_line, int fd)
{
	if (new_line)
		write(fd, "\n", 1);
}

int	echo(int ac, char **av, int	fd)
{
	int		i;
	int		j;
	bool	new_line;

	i = 1;
	while (i < ac && ft_strncmp(av[i], "-n", 2) == 0)
	{
		j = 1;
		while (av[i][j] && av[i][j] == 'n')
			j++;
		if (av[i][j] && av[i][j] != 'n')
			break ;
		i++;
	}
	new_line = i == 1;
	while (i < ac)
	{
		write(fd, av[i], ft_strlen(av[i]));
		if (i < ac - 1)
			write(fd, " ", 1);
		i++;
	}
	writeBackslashN(new_line, fd);
	g_conf.com->prev_ret = 0;
	return (0);
}
