#include "cub3d.h"
#include <stdio.h>

void 	get_img(t_tab *tab)
{
	if (!(tab->walls_tex.no.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,
	tab->prms.paths.no, &tab->walls_tex.no.width, &tab->walls_tex.no.height)))
		exit (0);
	if (!(tab->walls_tex.so.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,
	tab->prms.paths.so, &tab->walls_tex.so.width, &tab->walls_tex.so.height)))
		exit (0);
	if (!(tab->walls_tex.ea.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,
	tab->prms.paths.ea, &tab->walls_tex.ea.width, &tab->walls_tex.ea.height)))
		exit (0);
	if (!(tab->walls_tex.we.wall_img.img = mlx_xpm_file_to_image(tab->data.mlx,
	tab->prms.paths.we, &tab->walls_tex.we.width, &tab->walls_tex.we.height)))
		exit (0);
}

void 	get_addr(t_tab *tab)
{
	tab->walls_tex.no.wall_img.addr = mlx_get_data_addr(tab->walls_tex.no.wall_img.img,	&tab->walls_tex.no.wall_img.bpp, &tab->walls_tex.no.wall_img.line_l, &tab->walls_tex.no.wall_img.end);
	tab->walls_tex.so.wall_img.addr = mlx_get_data_addr(tab->walls_tex.so.wall_img.img, &tab->walls_tex.so.wall_img.bpp, &tab->walls_tex.so.wall_img.line_l, &tab->walls_tex.so.wall_img.end);
	tab->walls_tex.ea.wall_img.addr = mlx_get_data_addr(tab->walls_tex.ea.wall_img.img, &tab->walls_tex.ea.wall_img.bpp, &tab->walls_tex.ea.wall_img.line_l, &tab->walls_tex.ea.wall_img.end);
	tab->walls_tex.we.wall_img.addr = mlx_get_data_addr(tab->walls_tex.we.wall_img.img, &tab->walls_tex.we.wall_img.bpp, &tab->walls_tex.we.wall_img.line_l, &tab->walls_tex.we.wall_img.end);
}

unsigned int  *ft_pixel_take(t_wall_info tex, int x, int y)
{
	return ((unsigned int *)(tex.wall_img.addr +
							 (y * tex.wall_img.line_l + x * (tex.wall_img.bpp / 8))));
}

int check_some (t_tab *tab, char **str)
{
//	while ()
	return (0);
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

void            my_mlx_pixel_put(t_tab *tab, int x, int y, int color)
{
	char    *dst;

	dst = tab->data.addr + (y * tab->data.line_length + x * (tab->data.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		color_convert(t_tab *tab)
{
	tab->prms.clrs.floor_res = (tab->prms.clrs.floor_r << 16 | tab->prms.clrs.floor_g << 8 | tab->prms.clrs.floor_b);
	tab->prms.clrs.ceil_res = (tab->prms.clrs.ceil_r << 16 | tab->prms.clrs.ceil_g << 8 | tab->prms.clrs.ceil_b);
}

void	draw_floor_ceil(t_tab *tab)
{
	int x;
	int y;

	x = 0;
	y = 0;

	while (y < tab->prms.rsltn.y/2)
	{
		while (x < tab->prms.rsltn.x)
		{
			my_mlx_pixel_put(tab, x, y, tab->prms.clrs.ceil_res);
			x++;
		}
		x = 0;
		y++;
	}
	while (y < tab->prms.rsltn.y)
	{
		while (x < tab->prms.rsltn.x)
		{
			my_mlx_pixel_put(tab, x, y, tab->prms.clrs.floor_res);
			x++;
		}
		x = 0;
		y++;
	}
}

int		ft_press(int key, t_tab *tab)
{
	if (key == 13)
		tab->move.up = 1;
	if (key == 1)
		tab->move.down = 1;
	if (key == 124)
		tab->move.right = 1;
	if (key == 123)
		tab->move.left = 1;
	if (key == 2)
		tab->move.scroll_right = 1;
	if (key == 0)
		tab->move.scroll_left = 1;
	if (key == 53)
		exit(0);
	printf("key = %d\n", key);
	return (1);
}

int		ft_unpress(int key, t_tab *tab)
{
	if (key == 13)
		tab->move.up = 0;
	if (key == 1)
		tab->move.down = 0;
	if (key == 124)
		tab->move.right = 0;
	if (key == 123)
		tab->move.left = 0;
	if (key == 2)
		tab->move.scroll_right = 0;
	if (key == 0)
		tab->move.scroll_left = 0;
	return (1);
}

void	for_scroll_right(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_y * 0.06)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x += tab->pers.dir_y * 0.06;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y - tab->pers.dir_x * 0.06)] == '0')
	{
		tab->pers.pos_y -= tab->pers.dir_x * 0.06;
	}
}

void	for_scroll_left(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_y * 0.06)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x -= tab->pers.dir_y * 0.06;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y + tab->pers.dir_x * 0.06)] == '0')
	{
		tab->pers.pos_y += tab->pers.dir_x * 0.06;
	}
}

int		for_move(t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.075;
//	printf("KEY %d\n", key);
	if(tab->move.up)
	{
		if(tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '1' && tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '2')
			tab->pers.pos_x += tab->pers.dir_x * rotSpeed;
		if(tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y + tab->pers.dir_y * rotSpeed)] != '1' && tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y + tab->pers.dir_y * rotSpeed)] != '2')
			tab->pers.pos_y += tab->pers.dir_y * rotSpeed;
		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(tab->move.down)
	{
		if(tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '1' && tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '2')
			tab->pers.pos_x -= tab->pers.dir_x * rotSpeed;
		if(tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y - tab->pers.dir_y * rotSpeed)] != '1' && tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y - tab->pers.dir_y * rotSpeed)] != '2')
			tab->pers.pos_y -= tab->pers.dir_y * rotSpeed;
		write(1, "test2\n", 6);
	}
	//rotate to the right
	if (tab->move.right)
	{
		rotSpeed = 0.025;
		//both camera direction and camera plane must be rotated
		tab->ray.old_dir_x = tab->pers.dir_x;
		tab->pers.dir_x = tab->pers.dir_x * cos(-rotSpeed) - tab->pers.dir_y * sin(-rotSpeed);
		tab->pers.dir_y = tab->ray.old_dir_x * sin(-rotSpeed) + tab->pers.dir_y * cos(-rotSpeed);
		tab->ray.old_plane_x = tab->pers.plane_x;
		tab->pers.plane_x = tab->pers.plane_x * cos(-rotSpeed) - tab->pers.plane_y * sin(-rotSpeed);
		tab->pers.plane_y = tab->ray.old_plane_x * sin(-rotSpeed) + tab->pers.plane_y * cos(-rotSpeed);
	}
	//rotate to the left
	if (tab->move.left)
	{
		rotSpeed = 0.025;
		//both camera direction and camera plane must be rotated
		tab->ray.old_dir_x = tab->pers.dir_x;
		tab->pers.dir_x = tab->pers.dir_x * cos(rotSpeed) - tab->pers.dir_y * sin(rotSpeed);
		tab->pers.dir_y = tab->ray.old_dir_x * sin(rotSpeed) + tab->pers.dir_y * cos(rotSpeed);
		tab->ray.old_plane_x = tab->pers.plane_x;
		tab->pers.plane_x = tab->pers.plane_x * cos(rotSpeed) - tab->pers.plane_y * sin(rotSpeed);
		tab->pers.plane_y = tab->ray.old_plane_x * sin(rotSpeed) + tab->pers.plane_y * cos(rotSpeed);
	}
	if (tab->move.scroll_left)
		for_scroll_left(tab);
	if (tab->move.scroll_right)
		for_scroll_right(tab);
	draw_floor_ceil(tab);
	draw(tab);
	return (0);
	//rotate to the right
}

void		draw(t_tab *tab)
{
	int x = -1;
	//	W = 800;
	//	H = 600;
	while (++x < W)
	{
		tab->ray.camera_x = 2 * x / (double)W - 1; //x-coordinate in camera space
		tab->ray.ray_dir_x = tab->pers.dir_x + tab->pers.plane_x * tab->ray.camera_x;
		tab->ray.ray_dir_y = tab->pers.dir_y + tab->pers.plane_y * tab->ray.camera_x;

		//which box of the map we're in
		tab->ray.map_x = (int)tab->pers.pos_x;
		tab->ray.map_y = (int)tab->pers.pos_y;

		//length of ray from one x or y-side to next x or y-side
//		tab->ray.delta_dist_x = fabs(1 / tab->ray.ray_dir_x);
//		tab->ray.delta_dist_y = fabs(1 / tab->ray.ray_dir_y);
		tab->ray.delta_dist_x = (tab->ray.ray_dir_y == 0) ? 0 : ((tab->ray.ray_dir_x == 0) ? 1 : fabs(1 / tab->ray.ray_dir_x));
		tab->ray.delta_dist_y = (tab->ray.ray_dir_x == 0) ? 0 : ((tab->ray.ray_dir_y == 0) ? 1 : fabs(1 / tab->ray.ray_dir_y));

		tab->ray.hit = 0; //was there a wall hit?
		tab->ray.side_dist_x = 0;
		if(tab->ray.ray_dir_x < 0)
		{
			tab->ray.step_x = -1;
			tab->ray.side_dist_x = (tab->pers.pos_x - tab->ray.map_x) * tab->ray.delta_dist_x;
		}
		else
		{
			tab->ray.step_x = 1;
			tab->ray.side_dist_x = (tab->ray.map_x + 1.0 - tab->pers.pos_x) * tab->ray.delta_dist_x;
		}
		if(tab->ray.ray_dir_y < 0)
		{
			tab->ray.step_y = -1;
			tab->ray.side_dist_y = (tab->pers.pos_y - tab->ray.map_y) * tab->ray.delta_dist_y;
		}
		else
		{
			tab->ray.step_y = 1;
			tab->ray.side_dist_y = (tab->ray.map_y + 1.0 - tab->pers.pos_y) * tab->ray.delta_dist_y;
		}
		while (tab->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
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
			//Check if ray has hit a wall
			if (WWORLDMAP[tab->ray.map_x][tab->ray.map_y] == '1') tab->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (tab->ray.side == 0)
		{
			tab->ray.perp_wall_dist = (tab->ray.map_x - tab->pers.pos_x + (1.0 - tab->ray.step_x) / 2) / tab->ray.ray_dir_x;
//			printf("map_x - %d, pos_x - %f, dir_x - %f, perp_wall_dist - %f\n", tab->ray.map_x, tab->character.pos_x, tab->ray.ray_dir_x, tab->ray.perp_wall_dist);
		}
		else
		{
			tab->ray.perp_wall_dist = (tab->ray.map_y - tab->pers.pos_y + (1.0 - tab->ray.step_y) / 2) / tab->ray.ray_dir_y;
//			printf("map_y - %d, pos_y - %f, dir_y - %f, perp_wall_dist - %f\n", tab->ray.map_y, tab->character.pos_y, tab->ray.ray_dir_y, tab->ray.perp_wall_dist);
		}
		//Calculate height of line to draw on screen
		tab->ray.line_height = (int)(H / tab->ray.perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		tab->ray.draw_start = -tab->ray.line_height / 2 + H / 2;
		if(tab->ray.draw_start < 0) tab->ray.draw_start = 0;
		tab->ray.draw_end = tab->ray.line_height / 2 + H / 2;
		if(tab->ray.draw_end >= H) tab->ray.draw_end = H;

		//texturing calculations
		tab->ray.tex_num = WWORLDMAP[tab->ray.map_x][tab->ray.map_y] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wall_x
//		tab->ray.wall_x; //where exactly the wall was hit
		if(tab->ray.side == 0) tab->ray.wall_x = tab->pers.pos_y + tab->ray.perp_wall_dist * tab->ray.ray_dir_y;
		else tab->ray.wall_x = tab->pers.pos_x + tab->ray.perp_wall_dist * tab->ray.ray_dir_x;
		tab->ray.wall_x -= floor((tab->ray.wall_x));

		//x coordinate on the texture
		tab->ray.tex_x = (int)(tab->ray.wall_x * (double)texWidth);
		if(tab->ray.side == 0 && tab->ray.ray_dir_x > 0) tab->ray.tex_x = texWidth - tab->ray.tex_x - 1;
		if(tab->ray.side == 1 && tab->ray.ray_dir_y < 0) tab->ray.tex_x = texWidth - tab->ray.tex_x - 1;



		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		tab->ray.step = 1.0 * texHeight / tab->ray.line_height;
		// Starting texture coordinate
		tab->ray.tex_pos = (tab->ray.draw_start - H / 2.0 + tab->ray.line_height / 2.0) * tab->ray.step;
//		printf("x - %d\n", x);
//		printf("draw_start - %d\n", tab->ray.draw_start);
//		printf("draw_end - %d\n", tab->ray.draw_end);
		for(int y = tab->ray.draw_start; y < tab->ray.draw_end; y++)
		{
			t_wall_info tex;
			if (tab->ray.side == 0 && tab->ray.step_x > 0)
				tex = tab->walls_tex.so;
			else if (tab->ray.side == 0 && tab->ray.step_x < 0)
				tex = tab->walls_tex.no;
			else if (tab->ray.side == 1 && tab->ray.step_y > 0)
				tex = tab->walls_tex.ea;
			else
				tex = tab->walls_tex.we;
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			tab->ray.tex_y = (int)tab->ray.tex_pos & (texHeight - 1);
			tab->ray.tex_pos += tab->ray.step;
			/*if(tab->ray.side == 1)*/ tab->ray.color = ft_pixel_take(tex, tab->ray.tex_x, tab->ray.tex_y);//0xff00ff; // (tab->ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
			my_mlx_pixel_put(tab, x, y, (int)(*tab->ray.color));
		}
	}
	mlx_put_image_to_window(tab->data.mlx, tab->data.win, tab->data.img, 0, 0);
	mlx_destroy_image(tab->data.mlx, tab->data.img);
	tab->data.img = mlx_new_image(tab->data.mlx, W, H);
	tab->data.addr = mlx_get_data_addr(tab->data.img, &tab->data.bits_per_pixel, &tab->data.line_length, &tab->data.endian);
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


	tab.data.mlx = mlx_init();
	tab.data.win = mlx_new_window(tab.data.mlx, tab.prms.rsltn.x, tab.prms.rsltn.y, "Hui w rot!");
	tab.data.img = mlx_new_image(tab.data.mlx, tab.prms.rsltn.x, tab.prms.rsltn.y);
	tab.data.addr = mlx_get_data_addr(tab.data.img, &tab.data.bits_per_pixel, &tab.data.line_length, &tab.data.endian);
//	mlx_put_image_to_window(all.data.mlx, all.data.win, all.data.img, 0, 0);
	int x;
	get_img(&tab);
	get_addr(&tab);
	x = -1;
//	tab.pers.pos_x = 3.5;
//	tab.pers.pos_y = 3.5;
//	tab.pers.dir_x = 0.0;
//	tab.pers.dir_y = 1.0;
//	tab.pers.plane_x = 0.66;
//	tab.pers.plane_y = 0;
	draw(&tab);

	mlx_hook(tab.data.win, 2, (1L << 0), &ft_press, &tab);
	mlx_hook(tab.data.win, 3, (1L << 1), &ft_unpress, &tab);
	mlx_loop_hook(tab.data.mlx, &for_move, &tab);
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




