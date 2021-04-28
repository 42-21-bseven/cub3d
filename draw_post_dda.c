/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_post_dda.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:10:34 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:10:38 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	perf_dda(t_tab *tab)
{
	while (tab->ray.hit == 0)
	{
		if (tab->ray.side_dist_x < tab->ray.side_dist_y)
		{
			tab->ray.side_dist_x += tab->ray.delta_dist_x;
			tab->ray.map_x += tab->ray.step_x;
			tab->ray.side = 0;
		}
		else
		{
			tab->ray.side_dist_y += tab->ray.delta_dist_y;
			tab->ray.map_y += tab->ray.step_y;
			tab->ray.side = 1;
		}
		if (WWORLDMAP[tab->ray.map_x][tab->ray.map_y] == '1')
			tab->ray.hit = 1;
	}
}

void	calc_perpend_ray(t_tab *tab)
{
	if (tab->ray.side == 0)
	{
		tab->ray.perp_wall_dist = (tab->ray.map_x - \
			tab->pers.pos_x + (1.0 - tab->ray.step_x) / 2) / tab->ray.ray_dir_x;
	}
	else
	{
		tab->ray.perp_wall_dist = (tab->ray.map_y - \
			tab->pers.pos_y + (1.0 - tab->ray.step_y) / 2) / tab->ray.ray_dir_y;
	}
}

void	calc_line_texture_draw(t_tab *tab)
{
	tab->ray.line_height = (int)(H / tab->ray.perp_wall_dist);
	tab->ray.draw_start = -tab->ray.line_height / 2 + H / 2;
	if (tab->ray.draw_start < 0)
		tab->ray.draw_start = 0;
	tab->ray.draw_end = tab->ray.line_height / 2 + H / 2;
	if (tab->ray.draw_end >= H)
		tab->ray.draw_end = H;
	tab->ray.tex_num = WWORLDMAP[tab->ray.map_x][tab->ray.map_y] - 1;
	if (tab->ray.side == 0)
		tab->ray.wall_x = \
				tab->pers.pos_y + tab->ray.perp_wall_dist * tab->ray.ray_dir_y;
	else
		tab->ray.wall_x = \
				tab->pers.pos_x + tab->ray.perp_wall_dist * tab->ray.ray_dir_x;
	tab->ray.wall_x -= floor((tab->ray.wall_x));
	tab->ray.tex_x = (int)(tab->ray.wall_x * (double)TEX_WIDTH);
	if (tab->ray.side == 0 && tab->ray.ray_dir_x > 0)
		tab->ray.tex_x = TEX_WIDTH - tab->ray.tex_x - 1;
	if (tab->ray.side == 1 && tab->ray.ray_dir_y < 0)
		tab->ray.tex_x = TEX_WIDTH - tab->ray.tex_x - 1;
}

void	calc_size_texture(t_tab *tab, int x)
{
	int			y;
	t_wall_info	tex;

	y = tab->ray.draw_start;
	tab->ray.step = 1.0 * TEX_HEIGHT / tab->ray.line_height;
	tab->ray.tex_pos = \
		(tab->ray.draw_start - H / 2.0 \
								+ tab->ray.line_height / 2.0) * tab->ray.step;
	while (y < tab->ray.draw_end)
	{
		if (tab->ray.side == 0 && tab->ray.step_x > 0)
			tex = tab->walls_tex.so;
		else if (tab->ray.side == 0 && tab->ray.step_x < 0)
			tex = tab->walls_tex.no;
		else if (tab->ray.side == 1 && tab->ray.step_y > 0)
			tex = tab->walls_tex.ea;
		else
			tex = tab->walls_tex.we;
		tab->ray.tex_y = (int)tab->ray.tex_pos & (TEX_HEIGHT - 1);
		tab->ray.tex_pos += tab->ray.step;
		tab->ray.color = ft_pixel_take(tex, tab->ray.tex_x, tab->ray.tex_y);
		my_mlx_pixel_put(tab, x, y, (int)(*tab->ray.color));
		y++;
	}
}
