/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pre_dda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:02:54 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:02:57 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	calc_pos_and_direct(t_tab *tab, int x)
{
	tab->ray.camera_x = 2 * x / (double)W - 1;
	tab->ray.ray_dir_x = \
						tab->pers.dir_x + tab->pers.plane_x * tab->ray.camera_x;
	tab->ray.ray_dir_y = \
						tab->pers.dir_y + tab->pers.plane_y * tab->ray.camera_x;
	tab->ray.map_x = (int)tab->pers.pos_x;
	tab->ray.map_y = (int)tab->pers.pos_y;
}

void	calc_len_ray(t_tab *tab)
{
	if (tab->ray.ray_dir_y == 0)
	{
		tab->ray.delta_dist_x = 0;
	}
	else
	{
		if (tab->ray.ray_dir_x == 0)
			tab->ray.delta_dist_x = 1;
		else
			tab->ray.delta_dist_x = fabs(1 / tab->ray.ray_dir_x);
	}
	if (tab->ray.ray_dir_x == 0)
	{
		tab->ray.delta_dist_y = 0;
	}
	else
	{
		if (tab->ray.ray_dir_y == 0)
			tab->ray.delta_dist_y = 1;
		else
			tab->ray.delta_dist_y = fabs(1 / tab->ray.ray_dir_y);
	}
	tab->ray.hit = 0;
	tab->ray.side_dist_x = 0;
}

void	calc_step_and_side_dist(t_tab *tab)
{
	if (tab->ray.ray_dir_x < 0)
	{
		tab->ray.step_x = -1;
		tab->ray.side_dist_x = \
			(tab->pers.pos_x - tab->ray.map_x) * tab->ray.delta_dist_x;
	}
	else
	{
		tab->ray.step_x = 1;
		tab->ray.side_dist_x = \
			(tab->ray.map_x + 1.0 - tab->pers.pos_x) * tab->ray.delta_dist_x;
	}
	if (tab->ray.ray_dir_y < 0)
	{
		tab->ray.step_y = -1;
		tab->ray.side_dist_y = \
			(tab->pers.pos_y - tab->ray.map_y) * tab->ray.delta_dist_y;
	}
	else
	{
		tab->ray.step_y = 1;
		tab->ray.side_dist_y = \
			(tab->ray.map_y + 1.0 - tab->pers.pos_y) * tab->ray.delta_dist_y;
	}
}
