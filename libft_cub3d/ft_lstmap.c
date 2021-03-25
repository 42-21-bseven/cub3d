/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:25 by bseven            #+#    #+#             */
/*   Updated: 2020/11/18 19:12:27 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list *l;
	t_list *h;

	if (!lst)
		return (NULL);
	l = ft_lstnew(f(lst->content));
	if (!l)
		return (NULL);
	h = l;
	while (lst->next)
	{
		lst = lst->next;
		l->next = ft_lstnew(f(lst->content));
		if (!l)
		{
			ft_lstclear(&h, del);
			return (NULL);
		}
		l = l->next;
	}
	l->next = NULL;
	return (h);
}
