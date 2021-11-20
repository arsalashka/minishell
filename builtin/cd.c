/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:02:32 by maearly           #+#    #+#             */
/*   Updated: 2021/10/13 18:02:34 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"

int	cd_oldpwd(int fd)
{
	int		ret;
	char	*path;
	char	pwd[1025];

	ret = 0;
	g_conf.com->prev_ret = 0;
	path = getVar(g_conf.envp, "OLDPWD");
	if (!path)
		return (pError("cd", NULL, "OLDPWD not set", 1));
	if (!path[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	else
		ret = chdir(path);
	if (ret == -1)
		return (pError("cd", path, NULL, 1));
	getcwd(pwd, 1024);
	write(fd, pwd, ft_strlen(pwd));
	write(fd, "\n", 1);
	return (0);
}

int	cd(int ac, char **av, int fd)
{
	int		ret;
	char	pwd[1025];

	ret = 0;
	if (ac == 1)
		ret = chdir(getVar(g_conf.envp, "HOME"));
	if (ac >= 2 && ft_strcmp(av[1], "-") == 0)
	{
		if (cd_oldpwd(fd) == 1)
			return (1);
	}
	else if (ac >= 2 && av[1][0])
		ret = chdir(av[1]);
	if (ret == -1)
		return (pError("cd", av[1], NULL, 1));
	setVar2(g_conf.envp, "OLDPWD", getVar(g_conf.envp, "PWD"), false);
	getcwd(pwd, 1024);
	setVar2(g_conf.envp, "PWD", pwd, false);
	if (g_conf.prompt)
		free(g_conf.prompt);
	g_conf.prompt = ft_strjoin(pwd, " $ ");
	return (0);
}
