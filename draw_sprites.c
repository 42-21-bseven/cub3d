/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:00:34 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:00:41 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	calc_distance(t_tab *tab)
{
	int i;

	i = 0;
	while (i < tab->sprites.count_sprites)
	{
		tab->sprites.arr_spr[i].dist = ((tab->pers.pos_x \
				- tab->sprites.arr_spr[i].x) * (tab->pers.pos_x \
					- tab->sprites.arr_spr[i].x) + (tab->pers.pos_y \
											- tab->sprites.arr_spr[i].y) \
							* (tab->pers.pos_y - tab->sprites.arr_spr[i].y));
		i++;
	}
	bubble_sort(tab->sprites.arr_spr, tab->sprites.count_sprites);
}

void	translate_and_transform(t_tab *tab, int i)
{
	tab->ray_spr.sprite_x = tab->sprites.arr_spr[i].x - tab->pers.pos_x + 0.5;
	tab->ray_spr.sprite_y = tab->sprites.arr_spr[i].y - tab->pers.pos_y + 0.5;
	tab->ray_spr.inv_det = 1.0 / (tab->pers.plane_x * tab->pers.dir_y \
										- tab->pers.dir_x * tab->pers.plane_y);
	tab->ray_spr.form_x = \
	tab->ray_spr.inv_det * (tab->pers.dir_y * tab->ray_spr.sprite_x \
									- tab->pers.dir_x * tab->ray_spr.sprite_y);
	tab->ray_spr.form_y = tab->ray_spr.inv_det * (-tab->pers.plane_y \
		* tab->ray_spr.sprite_x + tab->pers.plane_x * tab->ray_spr.sprite_y);
	tab->ray_spr.spr_screen_x = (int)((W / 2) \
							* (1 + tab->ray_spr.form_x / tab->ray_spr.form_y));
}

void	calc_line_texture_sprite(t_tab *tab)
{
	tab->ray_spr.spr_height = abs((int)(H / (tab->ray_spr.form_y)));
	tab->ray_spr.draw_start_y = -tab->ray_spr.spr_height / 2 + H / 2;
	if (tab->ray_spr.draw_start_y < 0)
		tab->ray_spr.draw_start_y = 0;
	tab->ray_spr.draw_end_y = tab->ray_spr.spr_height / 2 + H / 2;
	if (tab->ray_spr.draw_end_y >= H)
		tab->ray_spr.draw_end_y = H;
	tab->ray_spr.sprite_width = abs((int)(W / (tab->ray_spr.form_y)));
	tab->ray_spr.draw_start_x = -tab->ray_spr.sprite_width / 2 \
												+ tab->ray_spr.spr_screen_x;
	if (tab->ray_spr.draw_start_x < 0)
		tab->ray_spr.draw_start_x = 0;
	tab->ray_spr.draw_end_x = tab->ray_spr.sprite_width / 2 \
												+ tab->ray_spr.spr_screen_x;
	if (tab->ray_spr.draw_end_x >= W)
		tab->ray_spr.draw_end_x = W;
}

void	perf_dda_sprite(t_tab *tab, int y)
{
	int stripe;

	stripe = --tab->ray_spr.draw_start_x;
	while (++stripe < tab->ray_spr.draw_end_x)
	{
		tab->ray_spr.tex_x = (int)(256 * (stripe \
		- (-tab->ray_spr.sprite_width / 2 + tab->ray_spr.spr_screen_x)) \
							* TEX_WIDTH / tab->ray_spr.sprite_width) / 256;
		if (tab->ray_spr.form_y > 0 && stripe >= 0 && stripe < W &&
			tab->ray_spr.form_y < tab->ray.z_buffer[stripe])
			y = tab->ray_spr.draw_start_y;
		while (y < tab->ray_spr.draw_end_y)
		{
			tab->ray_spr.d = (y) * 256 - H * 128 + \
			tab->ray_spr.spr_height * 128;
			tab->ray_spr.tex_y = ((tab->ray_spr.d * \
			TEX_HEIGHT) / tab->ray_spr.spr_height) / 256;
			tab->ray_spr.color = ft_pixel_take_spr(tab->sprites.spr_img, \
			tab->ray_spr.tex_x, tab->ray_spr.tex_y);
			if ((int)(*tab->ray_spr.color) != 0x000000)
				my_mlx_pixel_put(tab, stripe, y, (int)(*tab->ray_spr.color));
			y++;
		}
	}
}
