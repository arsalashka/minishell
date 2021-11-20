/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func_tail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:46:14 by megen             #+#    #+#             */
/*   Updated: 2021/11/16 13:54:08 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/func.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buf;
	int		i;

	if (!s)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * len + 1);
	if (NULL == buf)
		return (NULL);
	i = 0;
	while (start < ft_strlen(s) && len--)
	{
		buf[i] = s[i + start];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && (unsigned char)s1[i] == (unsigned char)s2[i]
		&& i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	len;

	if (!dst)
		return (0);
	i = 0;
	len = ft_strlen(src);
	while (i < (int)dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize)
		dst[i] = '\0';
	return (len);
}

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	num = 0;
	sign = 1;
	while (*(str + i) == '\n' || *(str + i) == '\t' || *(str + i) == '\r'
		|| *(str + i) == '\v' || *(str + i) == '\f' || *(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
		num = num * 10 + (*(str + i++) - '0');
	return (num * sign);
}
