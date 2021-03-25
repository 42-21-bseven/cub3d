/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 19:10:27 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 17:27:42 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned const char	*s;
	unsigned char		symbol;

	symbol = c;
	s = str;
	if (n != 0)
	{
		while (n-- > 0)
		{
			if (*s++ == symbol)
				return ((void *)--s);
		}
	}
	return (0);
}
