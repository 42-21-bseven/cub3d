/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:28:37 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 19:10:51 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *list1;
	t_list *list2;

	list1 = *lst;
	while (list1)
	{
		list2 = list1->next;
		ft_lstdelone(list1, del);
		list1 = list2;
	}
	*lst = NULL;
}
