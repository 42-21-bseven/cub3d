/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:09:37 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 19:10:05 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *n;

	if (lst)
	{
		if (*lst)
		{
			n = ft_lstlast(*lst);
			n->next = new;
		}
		else
			*lst = new;
	}
}
