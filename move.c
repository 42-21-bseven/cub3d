/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:45:50 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:45:58 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int		ft_press(int key, t_tab *tab)
{
	if (key == 13)
		tab->move.up = 1;
	if (key == 1)
		tab->move.down = 1;
	if (key == 124)
		tab->move.right = 1;
	if (key == 123)
		tab->move.left = 1;
	if (key == 2)
		tab->move.scroll_right = 1;
	if (key == 0)
		tab->move.scroll_left = 1;
	if (key == 53)
		exit(0);
	return (1);
}

int		ft_unpress(int key, t_tab *tab)
{
	if (key == 13)
		tab->move.up = 0;
	if (key == 1)
		tab->move.down = 0;
	if (key == 124)
		tab->move.right = 0;
	if (key == 123)
		tab->move.left = 0;
	if (key == 2)
		tab->move.scroll_right = 0;
	if (key == 0)
		tab->move.scroll_left = 0;
	return (1);
}

void	for_rotate_right(t_tab *tab)
{
	double	rot_speed;

	rot_speed = 0.025;
	tab->ray.old_dir_x = tab->pers.dir_x;
	tab->pers.dir_x = tab->pers.dir_x \
			* cos(-rot_speed) - tab->pers.dir_y * sin(-rot_speed);
	tab->pers.dir_y = tab->ray.old_dir_x \
			* sin(-rot_speed) + tab->pers.dir_y * cos(-rot_speed);
	tab->ray.old_plane_x = tab->pers.plane_x;
	tab->pers.plane_x = tab->pers.plane_x \
			* cos(-rot_speed) - tab->pers.plane_y * sin(-rot_speed);
	tab->pers.plane_y = tab->ray.old_plane_x \
			* sin(-rot_speed) + tab->pers.plane_y * cos(-rot_speed);
}

void	for_rotate_left(t_tab *tab)
{
	double	rot_speed;

	rot_speed = 0.025;
	tab->ray.old_dir_x = tab->pers.dir_x;
	tab->pers.dir_x = \
		tab->pers.dir_x * cos(rot_speed) - tab->pers.dir_y * sin(rot_speed);
	tab->pers.dir_y = \
		tab->ray.old_dir_x * sin(rot_speed) + tab->pers.dir_y * cos(rot_speed);
	tab->ray.old_plane_x = tab->pers.plane_x;
	tab->pers.plane_x = \
		tab->pers.plane_x * cos(rot_speed) - tab->pers.plane_y * sin(rot_speed);
	tab->pers.plane_y = tab->ray.old_plane_x \
		* sin(rot_speed) + tab->pers.plane_y * cos(rot_speed);
}

int		ft_move(t_tab *tab)
{
	if (tab->move.up)
		for_move_up(tab);
	if (tab->move.down)
		for_move_down(tab);
	if (tab->move.right)
		for_rotate_right(tab);
	if (tab->move.left)
		for_rotate_left(tab);
	if (tab->move.scroll_left)
		for_scroll_left(tab);
	if (tab->move.scroll_right)
		for_scroll_right(tab);
	draw(tab);
	return (0);
}
