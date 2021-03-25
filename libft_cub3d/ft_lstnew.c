/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:29:20 by bseven            #+#    #+#             */
/*   Updated: 2020/11/20 21:46:49 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *newelement;

	newelement = (t_list *)malloc(sizeof(t_list));
	if (newelement)
	{
		newelement->content = content;
		newelement->next = NULL;
	}
	else
		return (NULL);
	return (newelement);
}
