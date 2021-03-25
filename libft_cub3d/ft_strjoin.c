/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:47:39 by bseven            #+#    #+#             */
/*   Updated: 2020/11/20 21:04:40 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*g;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(((ft_strlen(s1)) + (ft_strlen(s2)) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	g = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = 0;
	return (g);
}
