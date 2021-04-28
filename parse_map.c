/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:56:37 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:56:41 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_map(t_tab *tab, char *str, t_list **map)
{
	if (search_map(tab, str) && tab->flags.map != 1)
		return (-1 + (tab->check_flag = 0));
	if (tab->check_flag && rude_anal(tab, str, " 012NEWS\0"))
	{
		ft_lstadd_back(map, ft_lstnew(str));
		return (1);
	}
	ft_lstadd_back(map, ft_lstnew(str));
	return (0);
}

int		search_map(t_tab *tab, char *str)
{
	int k;

	k = 0;
	while (*str)
	{
		if (*str == 32 && ++k)
			str++;
		else if (*str == '1')
			return (tab->flags.map = 1);
		else
			return (tab->check_flag = 0);
	}
	if (k == 0)
	{
		if (tab->flags.map == 1 && (tab->flags.map = 3))
			return (1);
		if (tab->flags.map == 3)
			return (put_error("ERROR\nInvalid map\n"));
	}
	return (tab->flags.map = 1);
}

void	how_list_size(t_tab *tab, t_list *map)
{
	tab->iters.n = 0;
	tab->lst_len = 0;
	tab->lst_size = 0;
	while (map)
	{
		if ((tab->iters.n = ft_strlen((char *)map->content)) > tab->lst_len)
			tab->lst_len = tab->iters.n;
		map = map->next;
		tab->lst_size++;
	}
	tab->lst_size += 2;
	tab->lst_len += 2;
}

int		mem_for_map(t_tab *tab)
{
	tab->iters.i = 0;
	if (!(tab->a.arr = ft_calloc(tab->lst_size + 1, sizeof(char *))))
		return (-1 + (tab->check_flag = 0));
	while (tab->iters.i < tab->lst_size)
	{
		if (!(tab->a.arr[tab->iters.i++] =
					ft_calloc(tab->lst_len + 1, sizeof(char))))
			return (-1 + (tab->check_flag = 0));
	}
	return (1);
}

void	map_to_array(t_tab *tab, t_list *list)
{
	t_list *map;

	tab->iters.i = 0;
	map = list;
	while (tab->iters.i < tab->lst_size - 1)
	{
		if (tab->iters.i == 0)
			str_to_str("\0", tab->a.arr[tab->iters.i], tab->lst_len);
		else
		{
			str_to_str(map->content, tab->a.arr[tab->iters.i], tab->lst_len);
			map = map->next;
		}
		tab->iters.i++;
	}
	str_to_str("\0", tab->a.arr[tab->iters.i], tab->lst_len);
	free_list(&list);
}
