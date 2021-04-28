/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 05:20:22 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 05:20:25 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	parser(t_tab *tab, char **line, t_list *map, int fd)
{
	initial_parse(tab);
	ft_create_parse(tab, *line, &map, fd);
	how_list_size(tab, map);
	mem_for_map(tab);
	map_to_array(tab, map);
	map_anal(tab);
	color_convert(tab);
}

void	raycast_or_screen(t_tab *tab, int argc, char **av)
{
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (!(ft_strncmp(av[2], "--save", ft_strlen("--save"))))
			{
				tab->screen = 1;
				screen_size(tab);
				for_mlx_initial_window(tab);
				for_sprite_draw(tab);
				draw(tab);
				fr_screenshot(tab);
			}
			else
				put_error("Error\nInvalid argument\n");
		}
		else
		{
			screen_size(tab);
			for_mlx_initial_window(tab);
			for_sprite_draw(tab);
			for_mlx_loop_hook(tab);
		}
	}
}

int		main(int argc, char **argv)
{
	t_tab	tab;
	t_list	*map;
	int		fd;
	char	*line;

	map = NULL;
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (read(fd, &line, 0) < 0)
	{
		put_error("Error\nIt is directory\n");
	}
	parser(&tab, &line, map, fd);
	close(fd);
	raycast_or_screen(&tab, argc, argv);
	free_list(&map);
	free_struct(&tab);
	return (0);
}
