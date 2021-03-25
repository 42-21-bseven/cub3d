/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 02:19:33 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 18:03:58 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*d;
	const char	*s;
	size_t		nsize;
	size_t		ldst;

	d = dst;
	s = src;
	nsize = 0;
	while (*dst != '\0' && nsize++ < size)
		dst++;
	ldst = dst - d;
	nsize = size - ldst;
	if (nsize-- == 0)
		return (ldst + ft_strlen(src));
	while (*src != '\0')
	{
		if (nsize != 0)
		{
			*dst++ = *src;
			nsize--;
		}
		src++;
	}
	*dst = '\0';
	return (ldst + (src - s));
}
