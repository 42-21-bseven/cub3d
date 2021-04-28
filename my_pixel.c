/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:56:12 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:56:15 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			my_mlx_pixel_put(t_tab *tab, int x, int y, int color)
{
	char	*dst;

	dst = tab->data.addr + \
	(y * tab->data.line_length + x * (tab->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	*ft_pixel_take(t_wall_info tex, int x, int y)
{
	return ((unsigned int *)(tex.wall_img.addr +\
	(y * tex.wall_img.line_l + x * (tex.wall_img.bpp / 8))));
}

unsigned int	*ft_pixel_take_spr(t_img spr_img, int x, int y)
{
	return ((unsigned int *)(spr_img.addr +\
	(y * spr_img.line_l + x * (spr_img.bpp / 8))));
}
