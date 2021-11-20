/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:20 by maearly           #+#    #+#             */
/*   Updated: 2021/10/21 16:37:21 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include <sys/stat.h>

typedef struct s_error
{
	bool	isError;
	char	*errorMsg;
}	t_error;

int			pError(char *arg, char *arg2, char *message, int code);

#endif
