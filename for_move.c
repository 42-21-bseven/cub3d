/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 04:00:33 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 04:00:37 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	for_move_up(t_tab *tab)
{
	double rot_speed;

	rot_speed = 0.085;
	if (tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_x * rot_speed * 1.5)]\
		[(int)(tab->pers.pos_y)] == '0')
		tab->pers.pos_x += tab->pers.dir_x * rot_speed;
	if (tab->a.arr[(int)(tab->pers.pos_x)]\
		[(int)(tab->pers.pos_y + tab->pers.dir_y * rot_speed)] == '0')
		tab->pers.pos_y += tab->pers.dir_y * rot_speed;
}

void	for_move_down(t_tab *tab)
{
	double rot_speed;

	rot_speed = 0.085;
	if (tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_x * rot_speed * 1.5)]\
		[(int)(tab->pers.pos_y)] == '0')
		tab->pers.pos_x -= tab->pers.dir_x * rot_speed;
	if (tab->a.arr[(int)(tab->pers.pos_x)]\
		[(int)(tab->pers.pos_y - tab->pers.dir_y * rot_speed)] == '0')
		tab->pers.pos_y -= tab->pers.dir_y * rot_speed;
}

void	for_scroll_right(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_y * 0.17)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x += tab->pers.dir_y * 0.08;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y - tab->pers.dir_x * 0.17)] == '0')
	{
		tab->pers.pos_y -= tab->pers.dir_x * 0.08;
	}
}

void	for_scroll_left(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_y * 0.17)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x -= tab->pers.dir_y * 0.08;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y + tab->pers.dir_x * 0.17)] == '0')
	{
		tab->pers.pos_y += tab->pers.dir_x * 0.08;
	}
}
