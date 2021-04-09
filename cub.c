#include "cub3d.h"
#include <stdio.h>

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

int ft_create_parse(t_tab *tab, char *line, t_list **map, int fd)
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

int		key_press(int key, t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.05;
	printf("KEY %d\n", key);
	if(key == 65362)
	{
		if(tab->a.arr[(int)(tab->pers.posX + tab->pers.dirX * rotSpeed)][(int)(tab->pers.posY)] != '1')
			tab->pers.posX += tab->pers.dirX * rotSpeed;
		if(tab->a.arr[(int)(tab->pers.posX)][(int)(tab->pers.posY + tab->pers.dirY * rotSpeed)] != '1')
			tab->pers.posY += tab->pers.dirY * rotSpeed;
		write(1, "test\n", 5);
	}
	//move backwards if no wall behind you
	if(key == 65364)
	{
		if(tab->a.arr[(int)(tab->pers.posX - tab->pers.dirX * rotSpeed)][(int)(tab->pers.posY)] != '1')
			tab->pers.posX -= tab->pers.dirX * rotSpeed;
		if(tab->a.arr[(int)(tab->pers.posX)][(int)(tab->pers.posY - tab->pers.dirY * rotSpeed)] != '1')
			tab->pers.posY -= tab->pers.dirY * rotSpeed;
		write(1, "test2\n", 6);
	}
	//rotate to the right
	if (key == 65361)
	{
		//both camera direction and camera plane must be rotated
		tab->ray.oldDirX = tab->pers.dirX;
		tab->pers.dirX = tab->pers.dirX * cos(-rotSpeed) - tab->pers.dirY * sin(-rotSpeed);
		tab->pers.dirY = tab->ray.oldDirX * sin(-rotSpeed) + tab->pers.dirY * cos(-rotSpeed);
		tab->ray.oldPlaneX = tab->pers.planeX;
		tab->pers.planeX = tab->pers.planeX * cos(-rotSpeed) - tab->pers.planeY * sin(-rotSpeed);
		tab->pers.planeY = tab->ray.oldPlaneX * sin(-rotSpeed) + tab->pers.planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (key == 65363)
	{
		//both camera direction and camera plane must be rotated
		tab->ray.oldDirX = tab->pers.dirX;
		tab->pers.dirX = tab->pers.dirX * cos(rotSpeed) - tab->pers.dirY * sin(rotSpeed);
		tab->pers.dirY = tab->ray.oldDirX * sin(rotSpeed) + tab->pers.dirY * cos(rotSpeed);
		tab->ray.oldPlaneX = tab->pers.planeX;
		tab->pers.planeX = tab->pers.planeX * cos(rotSpeed) - tab->pers.planeY * sin(rotSpeed);
		tab->pers.planeY = tab->ray.oldPlaneX * sin(rotSpeed) + tab->pers.planeY * cos(rotSpeed);
	}
	draw(tab);
	return (0);
	//rotate to the right
}

int		draw(t_tab *tab)
{
	int x = -1;
	W = 500;
	H = 500;
	while (++x < W)
	{
		tab->ray.cameraX = 2 * x / (double)W - 1; //x-coordinate in camera space
		tab->ray.rayDirX = tab->pers.dirX + tab->pers.planeX * tab->ray.cameraX;
		tab->ray.rayDirY = tab->pers.dirY + tab->pers.planeY * tab->ray.cameraX;

		//which box of the map we're in
		tab->ray.mapX = (int)tab->pers.posX;
		tab->ray.mapY = (int)tab->pers.posY;

		//length of ray from one x or y-side to next x or y-side
		tab->ray.deltaDistX = fabs(1 / tab->ray.rayDirX);
		tab->ray.deltaDistY = fabs(1 / tab->ray.rayDirY);

		tab->ray.hit = 0; //was there a wall hit?
		tab->ray.sideDistX = 0;
		if(tab->ray.rayDirX < 0)
		{
			tab->ray.stepX = -1;
			tab->ray.sideDistX = (tab->pers.posX - tab->ray.mapX) * tab->ray.deltaDistX;
		}
		else
		{
			tab->ray.stepX = 1;
			tab->ray.sideDistX = (tab->ray.mapX + 1.0 - tab->pers.posX) * tab->ray.deltaDistX;
		}
		if(tab->ray.rayDirY < 0)
		{
			tab->ray.stepY = -1;
			tab->ray.sideDistY = (tab->pers.posY - tab->ray.mapY) * tab->ray.deltaDistY;
		}
		else
		{
			tab->ray.stepY = 1;
			tab->ray.sideDistY = (tab->ray.mapY + 1.0 - tab->pers.posY) * tab->ray.deltaDistY;
		}
		while (tab->ray.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (tab->ray.sideDistX < tab->ray.sideDistY)
			{
				tab->ray.sideDistX += tab->ray.deltaDistX;
				tab->ray.mapX += tab->ray.stepX;
				tab->ray.side = 0;
			}
			else
			{
				tab->ray.sideDistY += tab->ray.deltaDistY;
				tab->ray.mapY += tab->ray.stepY;
				tab->ray.side = 1;
			}
			//Check if ray has hit a wall
			if (WWORLDMAP[tab->ray.mapY][tab->ray.mapX] == '1') tab->ray.hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (tab->ray.side == 0)
		{
			tab->ray.perpWallDist = (tab->ray.mapX - tab->pers.posX + (1.0 - tab->ray.stepX) / 2) / tab->ray.rayDirX;
//			printf("mapX - %d, posX - %f, dirX - %f, perpWallDist - %f\n", tab->ray.mapX, tab->character.posX, tab->ray.rayDirX, tab->ray.perpWallDist);
		}
		else
		{
			tab->ray.perpWallDist = (tab->ray.mapY - tab->pers.posY + (1.0 - tab->ray.stepY) / 2) / tab->ray.rayDirY;
//			printf("mapY - %d, posY - %f, dirY - %f, perpWallDist - %f\n", tab->ray.mapY, tab->character.posY, tab->ray.rayDirY, tab->ray.perpWallDist);
		}
		//Calculate height of line to draw on screen
		tab->ray.lineHeight = (int)(H / tab->ray.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		tab->ray.drawStart = -tab->ray.lineHeight / 2 + H / 2;
		if(tab->ray.drawStart < 0) tab->ray.drawStart = 0;
		tab->ray.drawEnd = tab->ray.lineHeight / 2 + H / 2;
		if(tab->ray.drawEnd >= H) tab->ray.drawEnd = H - 1;

		//texturing calculations
		tab->ray.texNum = WWORLDMAP[tab->ray.mapY][tab->ray.mapX] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		tab->ray.wallX; //where exactly the wall was hit
		if(tab->ray.side == 0) tab->ray.wallX = tab->pers.posY + tab->ray.perpWallDist * tab->ray.rayDirY;
		else tab->ray.wallX = tab->pers.posX + tab->ray.perpWallDist * tab->ray.rayDirX;
		tab->ray.wallX -= floor((tab->ray.wallX));

		//x coordinate on the texture
		tab->ray.texX = (int)(tab->ray.wallX * (double)texWidth);
		if(tab->ray.side == 0 && tab->ray.rayDirX > 0) tab->ray.texX = texWidth - tab->ray.texX - 1;
		if(tab->ray.side == 1 && tab->ray.rayDirY < 0) tab->ray.texX = texWidth - tab->ray.texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		tab->ray.step = 1.0 * texHeight / tab->ray.lineHeight;
		// Starting texture coordinate
		tab->ray.texPos = (tab->ray.drawStart - H / 2.0 + tab->ray.lineHeight / 2.0) * tab->ray.step;
//		printf("x - %d\n", x);
//		printf("drawStart - %d\n", tab->ray.drawStart);
//		printf("drawEnd - %d\n", tab->ray.drawEnd);
		for(int y = tab->ray.drawStart; y < tab->ray.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			tab->ray.texY = (int)tab->ray.texPos & (texHeight - 1);
			tab->ray.texPos += tab->ray.step;
			if(tab->ray.side == 1) tab->ray.color = 0xff00ff; // (tab->ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
			my_mlx_pixel_put(tab, x, y, 0xff0000); // tab->ray.color);
		}
	}
	mlx_put_image_to_window(tab->data.mlx, tab->data.win, tab->data.img, 0, 0);
	mlx_destroy_image(tab->data.mlx, tab->data.img);
	tab->data.img = mlx_new_image(tab->data.mlx, 500, 500);
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
	ft_initial(&tab);
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

	tab.data.mlx = mlx_init();
	tab.data.win = mlx_new_window(tab.data.mlx, 500, 500, "Hui w rot!");
	tab.data.img = mlx_new_image(tab.data.mlx, 500, 500);
	tab.data.addr = mlx_get_data_addr(tab.data.img, &tab.data.bits_per_pixel, &tab.data.line_length, &tab.data.endian);
//	mlx_put_image_to_window(all.data.mlx, all.data.win, all.data.img, 0, 0);
	int x;

	x = -1;
	tab.pers.posX = 5.0;
	tab.pers.posY = 5.0;
	tab.pers.dirX = -1.0;
	tab.pers.dirY = 0.0;
	tab.pers.planeX = 0.0;
	tab.pers.planeY = 0.66;
	draw(&tab);

	mlx_hook(tab.data.win, 2, (1L << 0), &key_press, &tab);
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




