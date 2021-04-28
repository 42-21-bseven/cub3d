/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:27:01 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:27:04 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	draw_floor_ceil(t_tab *tab)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < tab->prms.rsltn.y / 2)
	{
		while (x < tab->prms.rsltn.x)
			my_mlx_pixel_put(tab, x++, y, tab->prms.clrs.ceil_res);
		x = 0;
		y++;
	}
	while (y < tab->prms.rsltn.y)
	{
		while (x < tab->prms.rsltn.x)
			my_mlx_pixel_put(tab, x++, y, tab->prms.clrs.floor_res);
		x = 0;
		y++;
	}
}

void	color_convert(t_tab *tab)
{
	tab->prms.clrs.floor_res = (tab->prms.clrs.floor_r << 16 | \
	tab->prms.clrs.floor_g << 8 | tab->prms.clrs.floor_b);
	tab->prms.clrs.ceil_res = (tab->prms.clrs.ceil_r << 16 | \
	tab->prms.clrs.ceil_g << 8 | tab->prms.clrs.ceil_b);
}

void	draw_sprites(t_tab *tab)
{
	int i;

	i = -1;
	calc_distance(tab);
	while (++i < tab->sprites.count_sprites)
	{
		translate_and_transform(tab, i);
		calc_line_texture_sprite(tab);
		perf_dda_sprite(tab, tab->ray_spr.draw_start_y);
	}
}

void	draw(t_tab *tab)
{
	int x;

	x = -1;
	draw_floor_ceil(tab);
	while (++x < W)
	{
		calc_pos_and_direct(tab, x);
		calc_len_ray(tab);
		calc_step_and_side_dist(tab);
		perf_dda(tab);
		calc_perpend_ray(tab);
		calc_line_texture_draw(tab);
		calc_size_texture(tab, x);
		tab->ray.z_buffer[x] = tab->ray.perp_wall_dist;
	}
	draw_sprites(tab);
	if (tab->screen != 1)
	{
		mlx_put_image_to_window(tab->data.mlx, \
									tab->data.win, tab->data.img, 0, 0);
		mlx_destroy_image(tab->data.mlx, tab->data.img);
		tab->data.img = mlx_new_image(tab->data.mlx, W, H);
		tab->data.addr = mlx_get_data_addr(tab->data.img, \
		&tab->data.bits_per_pixel, &tab->data.line_length, &tab->data.endian);
	}
}
