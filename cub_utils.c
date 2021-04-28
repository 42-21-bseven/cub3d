/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:17:32 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:17:35 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int		get_count(t_tab *tab)
{
	return (tab->flags.obj + tab->flags.we + tab->flags.ea \
				+ tab->flags.so + tab->flags.no + tab->flags.rsltn \
										+ tab->flags.floor + tab->flags.ceil);
}

void	ft_create_parse(t_tab *tab, char *line, t_list **map, int fd)
{
	while (tab->check_flag && get_count(tab) != 8 && get_next_line(fd, &line))
	{
		cut_space(&line);
		parse_param(tab, line);
		free(line);
		line = NULL;
	}
	while (tab->check_flag && get_next_line(fd, &line))
	{
		parse_map(tab, line, map);
	}
	if (tab->check_flag)
		parse_map(tab, line, map);
}

void	screen_size(t_tab *tab)
{
	int x;
	int y;

	x = 0;
	y = 0;
	mlx_get_screen_size(tab->data.mlx, &x, &y);
	if (tab->screen == 1)
	{
		if (tab->prms.rsltn.x > 10000)
			tab->prms.rsltn.x = 10000;
		if (tab->prms.rsltn.y > 10000)
			tab->prms.rsltn.y = 10000;
	}
	else
	{
		if (tab->prms.rsltn.x > x)
			tab->prms.rsltn.x = x;
		if (tab->prms.rsltn.y > y)
			tab->prms.rsltn.y = y;
	}
}

int		ft_close(void)
{
	exit(0);
}
