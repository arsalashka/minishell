/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:27:36 by megen             #+#    #+#             */
/*   Updated: 2021/11/16 13:58:12 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "minishell.h"

size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_malloc(size_t size);
char	*ft_strdup(const char *s1);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalpha(int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
long	ft_atol(const char *str);
int		ft_isalnum(int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
