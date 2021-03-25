/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:25:26 by bseven            #+#    #+#             */
/*   Updated: 2020/11/20 21:36:02 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_size(int n)
{
	int size;

	size = 0;
	if (n == 0)
		return (2);
	if (n < 0)
		size += 2;
	else
		size++;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

void	ft_int_char(char *s, long n, int size)
{
	s[size--] = '\0';
	while (n > -1)
	{
		if (n >= 10)
		{
			s[size] = n % 10 + '0';
			n /= 10;
		}
		else
		{
			s[size] = n + '0';
			n = -1;
		}
		size--;
	}
}

char	*ft_itoa(int num)
{
	char	*s;
	int		size;
	long	n;

	n = num;
	size = ft_size(num);
	s = malloc(size);
	if (!s)
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		ft_int_char(s, (n * -1), --size);
	}
	else
		ft_int_char(s, n, --size);
	return (s);
}
