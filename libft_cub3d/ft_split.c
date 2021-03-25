/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:46:44 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 18:46:51 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_counter_word(const char *s, char c)
{
	size_t i;
	size_t n;
	size_t d;

	i = 0;
	n = 0;
	d = 0;
	while (s[i])
	{
		if (s[i] != c && d == 0)
		{
			d = 1;
			n++;
		}
		if (s[i] == c && d == 1)
			d = 0;
		i++;
	}
	return (n);
}

size_t	ft_len_ch(char const *s, char c)
{
	const char *g;

	g = s;
	while (*s != c && *s)
		s++;
	return (s - g);
}

void	*ft_free_mem(char **res, size_t i)
{
	while ((int)i >= 0)
	{
		free(res[i]);
		res[i] = NULL;
		i--;
	}
	free(res);
	res = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	n;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	n = ft_counter_word(s, c);
	res = (char **)malloc(sizeof(char *) * (n + 1));
	if (!res)
		return (NULL);
	while (n--)
	{
		while (*s == c && *s)
			s++;
		res[i] = ft_substr(s, 0, ft_len_ch(s, c));
		if (!res[i])
			return (ft_free_mem(res, i));
		s = s + ft_len_ch(s, c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
