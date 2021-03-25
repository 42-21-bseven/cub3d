/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:00:45 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 18:00:49 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	const char	*cpy;
	size_t		l;

	l = ft_strlen(s) + 1;
	cpy = malloc(l * sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memcpy((void *)cpy, s, l);
	return ((char *)cpy);
}
