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
	initial_parse(&tab);
	ft_create_parse(&tab, line, &map, fd);
	how_list_size(&tab, map);
	printf ("\nmem_check %d\n", mem_for_map(&tab));
	map_to_array(&tab, map);
//	map_anal(&tab);
	printf ("\nhard_anal %d\n", map_anal(&tab));
	printf("\nDUB %d\n", tab.iters.dub);
	printf("\nCHEAK_FLAG %d\n", tab.check_flag);


	printf("\nHello, World!\n\n");
	printf("R rslsn = %d %d\n\n", tab.prms.rsltn.x, tab.prms.rsltn.y);
	printf("F clrs = %d, %d, %d\n", tab.prms.clrs.floor_r, tab.prms.clrs.floor_g, tab.prms.clrs.floor_b);
	printf("C clrs = %d, %d, %d\n\n", tab.prms.clrs.ceil_r, tab.prms.clrs.ceil_g, tab.prms.clrs.ceil_b);
	printf("C paths =\n %s\n %s\n %s\n %s\n %s\n\n\n", tab.prms.paths.no, tab.prms.paths.so,
		tab.prms.paths.ea, tab.prms.paths.we, tab.prms.paths.obj);

	for (int i = 0; i < tab.lst_size; i++)
	{
		printf("=====>%s|\n", tab.a.arr[i]);
	}
	color_convert(&tab);
	printf("Sprite count = %d\n", tab.sprites.count_sprites);
	calc_distance(&tab);
	for (int l = 0; l < tab.sprites.count_sprites; l++)
	{
		printf("x = %f, y = %f dist = %f\n", tab.sprites.arr_spr[l].x, tab.sprites.arr_spr[l].y, tab.sprites.arr_spr[l].dist);
	}

	tab.data.mlx = mlx_init();
	tab.data.win = mlx_new_window(tab.data.mlx, tab.prms.rsltn.x, tab.prms.rsltn.y, "cub3D");
	tab.data.img = mlx_new_image(tab.data.mlx, tab.prms.rsltn.x, tab.prms.rsltn.y);
	tab.data.addr = mlx_get_data_addr(tab.data.img, \
	&tab.data.bits_per_pixel, &tab.data.line_length, &tab.data.endian);
//	mlx_put_image_to_window(all.data.mlx, all.data.win, all.data.img, 0, 0);
	int x;
	get_img(&tab);
	get_addr(&tab);
	get_img_spr(&tab);
	get_addr_spr(&tab);
	tab.ray.z_buffer = (double *)malloc(tab.prms.rsltn.x * sizeof(double));
	x = -1;
//	tab.pers.pos_x = 3.5;
//	tab.pers.pos_y = 3.5;
//	tab.pers.dir_x = 0.0;
//	tab.pers.dir_y = 1.0;
//	tab.pers.plane_x = 0.66;
//	tab.pers.plane_y = 0;
	draw(&tab);

	mlx_hook(tab.data.win, 17, 0, &ft_close, &tab);
	mlx_hook(tab.data.win, 2, (1L << 0), &ft_press, &tab);
	mlx_hook(tab.data.win, 3, (1L << 1), &ft_unpress, &tab);
	mlx_loop_hook(tab.data.mlx, &ft_move, &tab);
	mlx_loop(tab.data.mlx);

//	TODO Возвращает Invalid Map. вместо Invalid Path.

//	TODO Очистка списка
	free_list(&map);
//	while(map)
//	{
//		printf("%s$\n", (char *)map->content);
//		map = map->next;
//	}

//	TODO очистка матрицы
//	free_list(&map);
//	Конец очистки матрицы

//	TODO Очистка путей
	free_struct(&tab);
//	Конец очистки путей
	printf("\nlst_len = %d\nlst_size = %d\n", tab.lst_len, tab.lst_size);
	return 0;
}




