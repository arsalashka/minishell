/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:07:00 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 17:07:01 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define MINVAL "-9223372036854775808"
# define MAXVAL "9223372036854775807"

# include "minishell.h"

bool	isBuiltin(char *str);
int		echo(int ac, char **av, int fd);
int		cd(int ac, char **av, int fd);
int		export(int ac, char **av, int fd);
int		env(int fd);
int		ft_exit(int ac, char **av);
int		pwd(int fd);
int		unset(int ac, char **av);

#endif
