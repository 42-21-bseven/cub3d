/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:53:49 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:53:51 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

void	for_mlx_initial_window(t_tab *tab)
{
	tab->data.mlx = mlx_init();
	tab->data.win = mlx_new_window(tab->data.mlx, tab->prms.rsltn.x, \
												tab->prms.rsltn.y, "cub3D");
	tab->data.img = mlx_new_image(tab->data.mlx, tab->prms.rsltn.x, \
															tab->prms.rsltn.y);
	tab->data.addr = mlx_get_data_addr(tab->data.img, \
	&tab->data.bits_per_pixel, &tab->data.line_length, &tab->data.endian);
}

void	for_mlx_loop_hook(t_tab *tab)
{
	mlx_hook(tab->data.win, 17, 0, &ft_close, tab);
	mlx_hook(tab->data.win, 2, (1L << 0), &ft_press, tab);
	mlx_hook(tab->data.win, 3, (1L << 1), &ft_unpress, tab);
	mlx_loop_hook(tab->data.mlx, &ft_move, tab);
	mlx_loop(tab->data.mlx);
}

void	for_sprite_draw(t_tab *tab)
{
	get_img(tab);
	get_addr(tab);
	get_img_spr(tab);
	get_addr_spr(tab);
	tab->ray.z_buffer = (double *)malloc(tab->prms.rsltn.x * sizeof(double));
}
