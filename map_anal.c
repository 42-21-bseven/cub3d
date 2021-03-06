/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_anal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:54:12 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:54:15 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rude_anal(t_tab *tab, char *str, char *head)
{
	char *right;

	while (*str)
	{
		if (*str == '2')
			tab->sprites.count_sprites++;
		right = head;
		while (*right)
		{
			if (*str == 'N' || *str == 'E' || *str == 'W' || *str == 'S')
			{
				tab->iters.dub++;
				break ;
			}
			if (*str == *right)
				break ;
			right++;
		}
		if (*right == '\0')
			return (tab->check_flag = put_error("\nERROR!\nInvalid Map\n"));
		if (tab->iters.dub > 1)
			return (put_error("\nERROR!\nDouble Personage\n"));
		str++;
	}
	return (1);
}

int	help_anal(t_tab *tab, char *err, int i, int j)
{
	if (tab->a.arr[i][j] == '2')
	{
		tab->sprites.arr_spr[tab->iters.k].x = i;
		tab->sprites.arr_spr[tab->iters.k++].y = j;
	}
	if (tab->a.arr[i][j] == 32)
	{
		if (hard_anal(tab, i, j) == -1)
			return (-1 + (tab->check_flag = put_error(err)));
	}
	if (tab->a.arr[i][j] == 'N' || tab->a.arr[i][j] == 'S' \
		|| tab->a.arr[i][j] == 'E' || tab->a.arr[i][j] == 'W')
	{
		tab->pers.pos_x = i + 0.5;
		tab->pers.pos_y = j + 0.5;
		tab->pers.orient = tab->a.arr[i][j];
		tab->a.arr[i][j] = '0';
	}
	pers_orient(tab);
	pers_orient_2(tab);
	return (1);
}

int	map_anal(t_tab *tab)
{
	int		i;
	int		j;
	char	*err;

	i = 0;
	tab->iters.k = 0;
	tab->sprites.arr_spr = \
			(t_spr*)malloc(tab->sprites.count_sprites * sizeof(t_spr));
	err = "\nERROR!\nInvalid Map.\n";
	if (tab->iters.dub == 0)
		return (tab->check_flag = put_error(err));
	while (i < tab->lst_size)
	{
		j = 0;
		while (j < tab->lst_len)
		{
			help_anal(tab, err, i, j);
			j++;
		}
		i++;
	}
	return (1);
}

int	hard_anal(t_tab *tab, int i, int j)
{
	if (i != 0 && !(tab->a.arr[i - 1][j] == '1' || tab->a.arr[i - 1][j] == ' '
					|| tab->a.arr[i - 1][j] == '\0'))
		return (-1);
	if (i != 0 && j && !(tab->a.arr[i - 1][j + 1] == '1' ||
	tab->a.arr[i - 1][j + 1] == ' ' || tab->a.arr[i - 1][j + 1] == '\0'))
		return (-1);
	if (j != tab->lst_len && !(tab->a.arr[i][j + 1] == '1'
	|| tab->a.arr[i][j + 1] == ' ' || tab->a.arr[i][j + 1] == '\0'))
		return (-1);
	if ((i != tab->lst_size - 1) && !(tab->a.arr[i + 1][j + 1] == '1' ||
	tab->a.arr[i + 1][j + 1] == ' ' || tab->a.arr[i + 1][j + 1] == '\0'))
		return (-1);
	if (i != tab->lst_size - 1 && !(tab->a.arr[i + 1][j] == '1' ||
	tab->a.arr[i + 1][j] == ' ' || tab->a.arr[i + 1][j] == '\0'))
		return (-1);
	if (i != tab->lst_size - 1 && j != 0 && !(tab->a.arr[i + 1][j - 1] == '1'
	|| tab->a.arr[i + 1][j - 1] == ' ' || tab->a.arr[i + 1][j - 1] == '\0'))
		return (-1);
	if (j != 0 && !(tab->a.arr[i][j - 1] == '1' || tab->a.arr[i][j - 1] == ' '
					|| tab->a.arr[i][j - 1] == '\0'))
		return (-1);
	if ((j != 0 && i != 0) && !(tab->a.arr[i - 1][j - 1] == '1' ||
	tab->a.arr[i - 1][j - 1] == ' ' || tab->a.arr[i - 1][j - 1] == '\0'))
		return (-1);
	return (1);
}
