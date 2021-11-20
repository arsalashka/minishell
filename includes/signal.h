/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maearly <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 16:41:07 by maearly           #+#    #+#             */
/*   Updated: 2021/10/27 16:41:08 by maearly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

void	defineInputSignals(void);
void	defineExecSignals(void);
void	interruptHereDoc(int signal);
int		rl_set_signals(void);

#endif
