/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:27:33 by bseven            #+#    #+#             */
/*   Updated: 2021/01/26 01:29:13 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memcpy_gnl(char *dest, char *src, size_t n)
{
	char		*d;
	char		*s;

	d = dest;
	s = src;
	if (d == 0 && s == 0)
		return (NULL);
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup_gnl(char *s)
{
	char		*cpy;
	size_t		l;

	l = ft_strlen_gnl(s) + 1;
	cpy = malloc(l * sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy_gnl(cpy, s, l);
	return ((char *)cpy);
}

size_t	ft_strlen_gnl(char *s)
{
	const char *str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

int		freshka(t_struct *gnl, char *res, int retka)
{
	if (gnl->guf)
		free(gnl->guf);
	if (res)
		free(res);
	gnl->power = OFF;
	return (retka);
}
