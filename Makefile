# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megen <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 16:41:57 by maearly           #+#    #+#              #
#    Updated: 2021/11/18 20:59:38 by megen            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

LIST		=	srcs/main.c												\
			srcs/init.c			srcs/vars.c				srcs/vect.c		\
            error/error.c		srcs/vars2.c			srcs/vect2.c	\
            srcs/init2.c		srcs/vars3.c			srcs/signal.c	\
            srcs/readline.c		srcs/vars4.c	\
            srcs/path.c			srcs/vect3.c	\
			\
			builtin/runBuiltin.c	builtin/echo.c			builtin/cd.c \
			builtin/export.c		builtin/env.c			builtin/exit.c \
			builtin/pwd.c			builtin/unset.c							\
			ary/parser_ary.c		ary/inhereted.c			ary/utils.c	\
			ary/utils_add.c			ary/wrapper.c			\
			ft_func/ft_func_body.c \
			ft_func/ft_func_head.c \
			ft_func/ft_func_tail.c \
			ft_func/ft_func_add.c \
			ary/par_creation.c \
			ary/line_proc.c \
			ary/envp_start.c \
			ary/envp_end.c \
			ary/misc_head.c \
			ary/misc_body.c \
			ary/misc_tail.c \
			ary/parser.c \
			ary/node.c \
			ary/job_creation.c \
			ary/job_misc.c \
			ary/argv.c \
			ary/execute.c \
			ary/execute_add.c \
			ary/io.c \
			ary/syntax.c \
			ary/here_doc.c \
			ary/path.c \
			ary/path_add.c



LRL			=	-lreadline

 LDFLAGS	=	-L/Users/maearly/.brew/Cellar/readline/8.1.1/lib
 CPPFLAGS	=	-I/Users/maearly/.brew/Cellar/readline/8.1.1/include

#CPPFLAGS = -I/usr/include/readline
#LDFLAGS = -L/usr/lib/x86_64-linux-gnu

LIST_B		=

OBJ			=	$(patsubst %.c,%.o,$(LIST))

OBJ_B		=	$(patsubst %.c,%.o,$(LIST_B))

OPTFLAGS	=	-g

FLAGS		=	-Wall -Wextra -Werror

# LIBFT_DIR	=	./libft

# LIBFT_FLAGS	=	-L $(LIBFT_DIR) -lft

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			gcc $(FLAGS) $(OPTFLAGS) $(OBJ) -o $(NAME) $(LRL) $(LDFLAGS) $(CPPFLAGS)

bonus	:
			@make $(OBJ)="$(OBJ_B)" all

clean	:
			@rm -f $(OBJ) $(OBJ_B)

fclean	:	clean
			@rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re bonus
