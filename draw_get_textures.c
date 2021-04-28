/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_get_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:13:03 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:13:07 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	get_img(t_tab *tab)
{
	if (!(tab->walls_tex.no.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.no, &tab->walls_tex.no.width, &tab->walls_tex.no.height)))
		exit(0);
	if (!(tab->walls_tex.so.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.so, &tab->walls_tex.so.width, &tab->walls_tex.so.height)))
		exit(0);
	if (!(tab->walls_tex.ea.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.ea, &tab->walls_tex.ea.width, &tab->walls_tex.ea.height)))
		exit(0);
	if (!(tab->walls_tex.we.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.we, &tab->walls_tex.we.width, &tab->walls_tex.we.height)))
		exit(0);
}

void	get_addr(t_tab *tab)
{
	tab->walls_tex.no.wall_img.addr = \
	mlx_get_data_addr(tab->walls_tex.no.wall_img.img, \
	&tab->walls_tex.no.wall_img.bpp, &tab->walls_tex.no.wall_img.line_l, \
											&tab->walls_tex.no.wall_img.end);
	tab->walls_tex.so.wall_img.addr = \
	mlx_get_data_addr(tab->walls_tex.so.wall_img.img, \
	&tab->walls_tex.so.wall_img.bpp, &tab->walls_tex.so.wall_img.line_l, \
											&tab->walls_tex.so.wall_img.end);
	tab->walls_tex.ea.wall_img.addr = \
	mlx_get_data_addr(tab->walls_tex.ea.wall_img.img, \
	&tab->walls_tex.ea.wall_img.bpp, &tab->walls_tex.ea.wall_img.line_l, \
											&tab->walls_tex.ea.wall_img.end);
	tab->walls_tex.we.wall_img.addr = \
	mlx_get_data_addr(tab->walls_tex.we.wall_img.img, \
	&tab->walls_tex.we.wall_img.bpp, &tab->walls_tex.we.wall_img.line_l, \
											&tab->walls_tex.we.wall_img.end);
}
