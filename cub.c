#include "cub3d.h"
#include <stdio.h>

int 	ft_close(void)
{
	exit(0);
}

int get_count(t_tab *tab)
{
	return (tab->flags.obj + tab->flags.we + tab->flags.ea + tab->flags.so +
	tab->flags.no + tab->flags.rsltn + tab->flags.floor + tab->flags.ceil);
}

void ft_create_parse(t_tab *tab, char *line, t_list **map, int fd)
{
	while (tab->check_flag && get_count(tab) != 8 && get_next_line(fd, &line))
	{
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

void 	parser(t_tab *tab, char **line, t_list *map, int fd)
{
	initial_parse(tab);
	ft_create_parse(tab, *line, &map, fd);
	how_list_size(tab, map);
	mem_for_map(tab);
	map_to_array(tab, map);
	map_anal(tab);
	color_convert(tab);
}

void screen_size(t_tab *tab)
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

int main(int argc, char **argv)
{
//	argc = 2;
//	argv[1] = "/home/alexander/CLionProjects/cub/map_1.cub";
	t_tab tab;
	t_list *map;
	int fd;
	char *line;

	map = NULL;
	line = NULL;
	fd = open(argv[1], O_RDONLY);

	if (read(fd, &line, 0) < 0)
	{
		put_error("Error\nIt is directory\n");
	}
	parser(&tab, &line, map, fd);
	close(fd);
	if (argc == 2 || argc == 3)
	{
		if (argc == 3)
		{
			if (!(ft_strncmp(argv[2], "--save", ft_strlen("--save"))))
			{
				tab.screen = 1;
				screen_size(&tab);
				for_mlx_initial_window(&tab);
				for_sprite_draw(&tab);
				draw(&tab);
				fr_screenshot(&tab);
			}
			else
				put_error("Error\nInvalid argument\n");
		}
		else
		{
			screen_size(&tab);
			for_mlx_initial_window(&tab);
			for_sprite_draw(&tab);
			for_mlx_loop_hook(&tab);
		}
	}
	free_list(&map);
	free_struct(&tab);
	return 0;
}