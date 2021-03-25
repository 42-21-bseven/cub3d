/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:09:50 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 18:09:53 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *n;

	n = (char *)s;
	while (*s)
		s++;
	while (s != n - 1)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	return (0);
}
