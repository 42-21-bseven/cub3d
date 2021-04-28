/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:21:21 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:21:24 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_list(t_list **head)
{
	t_list *tmp;

	if (*head)
	{
		while ((*head)->next)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp->content);
			free(tmp);
		}
		if ((*head)->content)
			free((*head)->content);
		free(*head);
	}
}

void	free_struct(t_tab *tab)
{
	int i;

	i = 0;
	if (tab->prms.paths.obj)
		free(tab->prms.paths.obj);
	if (tab->prms.paths.ea)
		free(tab->prms.paths.ea);
	if (tab->prms.paths.we)
		free(tab->prms.paths.we);
	if (tab->prms.paths.so)
		free(tab->prms.paths.so);
	if (tab->prms.paths.no)
		free(tab->prms.paths.no);
	while (i < tab->lst_size)
		if (tab->a.arr[i])
			free(tab->a.arr[i++]);
	if (tab->a.arr)
		free(tab->a.arr);
}
