/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:52:30 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 17:52:57 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*d;

	i = 0;
	d = destination;
	while (i < n)
	{
		d[i] = c;
		i++;
	}
	return (destination);
}
