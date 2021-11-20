/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 13:11:45 by megen             #+#    #+#             */
/*   Updated: 2021/11/18 13:10:58 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef enum e_error_ary
{
	error_malloc = -13,
	error_syntax,
	error_nofile,
	error_noprem,
	error_nocom,
	error_create,
	error_open,
	error_fork,
	error_execve,
	error_waitpid,
	error_pipe,
	error_dupe,
	error_ambig,
}	t_error_ary;

typedef struct s_inh_node
{
	int					fd;
	struct s_inh_node	*next;
}t_inh_node;

typedef struct s_inh_list
{
	t_inh_node			*head;
	t_inh_node			*tail;
}t_inh_list;

typedef struct s_snode
{
	void			*value;
	struct s_snode	*next;
	struct s_snode	*prev;
}t_snode;

typedef struct s_pid_node
{
	int					pid;
	struct s_pid_node	*next;
}t_pid_node;

typedef struct s_pw_list
{
	t_pid_node	*head;
	t_pid_node	*tail;
}t_pw_list;

typedef struct s_argv_list
{
	int			size;
	t_snode		*head;
	t_snode		*tail;
}t_argv_list;

typedef struct s_par
{
	int				pid;
	int				fd_out;
	int				fd_in;
	int				fd_hd;
	int				error;
	bool			append;
	bool			heredoc;
	bool			input_err;
	bool			built_in;
	char			*path;
	char			**argv;
	char			**envp;
	char			*line;
	t_snode			*head;
	t_snode			*tail;
	t_snode			*error_node;
	t_snode			*out_node;
	t_snode			*in_node;
	t_snode			*exe;
	struct s_par	*next;	
}	t_par;

typedef struct s_com
{
	int			p[2];
	int			prev_ret;
	char		**envp;
	t_snode		*arg_start;
	t_snode		*arg_last;
	t_par		*par_head;
	t_par		*par_tail;
	t_inh_list	inh_list;
	t_pw_list	pw_list;
	int			syntax;
	bool		term;
	int			ac;
	char		**av;
}	t_com;

/*		utils.c */

int		ary_strlen(char *s);
char	*ary_strdup(char *src);
bool	ary_strcmp(char *src, char *trgt);
char	*trim_space(char *line);
int		make_file(char *name);

/*		utils_add.c */

char	**ft_split_ary(char const *s, char c);

/*		wrapper.c */

int		wr_open(t_com *cmd, char *name, int mode);
bool	wr_pipe(t_com *cmd, int *p);
bool	wr_close(t_com *cmd, int fd);

/*		inhereted.c */

void	close_inhereted(t_com *cmd, int in, int out);
bool	add_to_inh_list(t_inh_list *list, int fd);
int		count_args(char **av);

/*		par_creation.c */

bool	line_to_par(t_com *com, char *line);
void	free_par_slist(t_par *par);

/*		line_proc.c  */

bool	split_line_to_pars(t_com *com, char *line);

/*		envp_start.c */

bool	par_envp(t_com *com);

/*		envp_end.c */

char	*replace_envp(char *line, int place, int prev_ret, t_par *par);

/*		par_to_parse */

bool	par_to_parse(t_com *com);

/*		misc_head.c */

char	*quote_skip(char *line);
int		alt_quote_skip(char *line);
bool	chek_line(char s);
bool	chek_back(char *line, char *base);
bool	chek_empty(char *line);

/*		misc_body.c */

bool	find_next_spec(char *line, char spec);
void	chek_ambig(char *line, int place, t_par *par);
t_snode	*skip_par(t_snode *node);
int		is_com_sym(char *line);
void	free_all(t_com *com, t_par *par);

/*		misc_tail.c */

bool	err_set(t_par *par, int error);
int		get_size(char *line);
char	*sq_qutes(char *line);

/*		node.c */

bool	add_snode(t_com *com, char *line);
void	free_snode(t_snode *head);
bool	add_ambig_node(char *line, int place, int size, t_par *par);

/*		job_creation.c */

bool	reform_nodes(t_com *com);

/*		job_misc.c */

void	find_last_in(t_snode *node, t_par *par);
void	find_last_out(t_snode *node, t_par *par);
bool	prev_chek(t_snode *node);

/*		path.c */

bool	setup_path(t_com *com, t_par *par);

/*		path_add.c */

bool	tape_it(int ct, char **paths, char *name, char **path);

/*		argv.c */

bool	setup_argv(t_com *com, t_snode *node, t_par *par, t_argv_list *list);

/*		execute.c */

bool	execute_pipeline(t_com *com, t_par *par);

/*		io.c */

bool	i_o_setup(t_com *com, t_par *par);
void	setup_out(t_com *com, t_snode *node, t_par *par);

/*		execute_add.c */

bool	wait_all_pids(t_com *com);

/*		syntax.c */

bool	syntax_err(t_com *com, char *line);

/*		here_doc.c */

bool	here_doc(t_com *com);

bool	empty_line(char *line);
bool	is_com_node(char *line);
int		countArgc(t_com *com);

#endif
