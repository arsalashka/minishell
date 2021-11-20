/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:48:14 by maearly           #+#    #+#             */
/*   Updated: 2021/10/11 16:48:20 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "builtin.h"
# include "error.h"
# include "signal.h"
# include "header.h"
# include "func.h"

# define RED "\033[0;31m"
# define WHITE "\033[1;97m"
# define BLUE "\033[1;94m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

typedef struct s_var
{
	char	*raw;
	char	*key;
	char	*value;
}			t_var;

typedef struct s_vect
{
	void	**data;
	int		capacity;
	int		size;
}			t_vect;

typedef struct s_shell
{
	t_vect		*envp;
	char		*prompt;
	bool		forked;
	t_com		*com;
}	t_shell;

extern t_shell	g_conf;

void	initializate(int ac, char **av, char **env);
t_vect	*newVect(void);
t_vect	*newVector(size_t size);
t_var	*newVarS(char *var_str);
bool	checkCharKey(char *key);
bool	equalsKey(void *item1, void *item2);
int		indexOf(t_vect *envp, void *item, bool (*eqlKey)(void *, void *));
void	*removeAt(t_vect *envp, int pos);
void	deleteVar(void *var);
int		setVar2(t_vect *env, char *key, char *value, bool check);
void	*search(t_vect *this, void *item, bool (*eqlKey)(void *, void *));
void	insert(t_vect *envp, void *var);
int		updateShlvl(void);
t_var	*getVar2(t_vect *env, char *key);
char	*getVar(t_vect *env, char *key);
t_vect	*newVectorFrom(t_vect *other);
void	*at(t_vect *this, int pos);
int		is_empty(t_vect *envp);
void	delete(t_vect *this);
void	mainLoop(char **env);
int		setVar(t_vect *env, char *var_str);
bool	checkKey(t_var *var);
int		updateVar(t_var *var, t_var *new);
int		listVars(t_vect *env, bool sort_, int (*print)(t_var *, int), int fd);
int		predicate(void *s1, void *s2);
void	sorter(t_vect *this, int (*f)(void *, void *));
int		printVar2(t_var *var, int fd);
void	swap(t_vect *this, int pos1, int pos2);
void	deleteFree(t_vect *this, void (*f)(void *));
int		unsetVar(t_vect *env, char *key);
char	**extractEnvp(t_vect *g_env);
int		parser_ary(t_com *com, char *line);
int		execBuiltin(t_par *par);
bool	syntaxError(char *arg, char *arg2, char *message, int code);
void	handleErrors(t_par *par, bool ispath, int errno_);

#endif
