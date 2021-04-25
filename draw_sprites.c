#include "./cub3d.h"

void 	calc_ditantion(t_tab *tab)
{
	int i;

	i = 0;
	while (i < tab->sprites.count_sprites)
	{
//		write(1, "1", 1);
//		printf(" iter = %d\n", i);
		tab->sprites.arr_spr[i].dist = ((tab->pers.pos_x - tab->sprites.arr_spr[i].x) * (tab->pers.pos_x - tab->sprites.arr_spr[i].x) + (tab->pers.pos_y - tab->sprites.arr_spr[i].y) * (tab->pers.pos_y - tab->sprites.arr_spr[i].y));
//		tab->sprites.arr_spr[i].dist = i;
//		printf("distans on circle = %f\n", tab->sprites.arr_spr[i].dist);
//		printf("test x = %f, y = %f dist = %f\n", tab->sprites.arr_spr[i].x, tab->sprites.arr_spr[i].y, tab->sprites.arr_spr[i].dist);
		i++;
	}
//	write(1, "3", 1);
	bubble_sort(tab->sprites.arr_spr, tab->sprites.count_sprites);
//	write(1, "4", 1);
}

void 	bubble_sort(t_spr *tab, int count)
{
	t_spr t_temp;
	int i;
	int j;

	i = 1;
	while (i < count)
	{
		j = 0;
		while (j < count - 1)
		{
			if (tab[i].dist > tab[j].dist)
			{
				t_temp = tab[i];
				tab[i] = tab[j];
				tab[j] = t_temp;
			}
			j++;
		}
		i++;
	}
//	draw_sprites(tab);
}

void 	draw_sprites(t_tab *tab)
{
	int i;

	i = -1;
	while (++i < tab->sprites.count_sprites)
	{
		//translate sprite position to relative to camera
		tab->ray_spr.spriteX = tab->sprites.arr_spr[i].x - tab->pers.pos_x + 0.5;
		tab->ray_spr.spriteY = tab->sprites.arr_spr[i].y - tab->pers.pos_y + 0.5;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		tab->ray_spr.invDet = 1.0 / (tab->pers.plane_x * tab->pers.dir_y - tab->pers.dir_x *
											   tab->pers.plane_y); //required for correct matrix multiplication

		tab->ray_spr.transformX = tab->ray_spr.invDet * (tab->pers.dir_y * tab->ray_spr.spriteX - tab->pers.dir_x * tab->ray_spr.spriteY);
		tab->ray_spr.transformY = tab->ray_spr.invDet * (-tab->pers.plane_y * tab->ray_spr.spriteX + tab->pers.plane_x *
																					 tab->ray_spr.spriteY); //this is actually the depth inside the screen, that what Z is in 3D
		tab->ray_spr.spriteScreenX =
		(int)((W / 2) *(1 + tab->ray_spr.transformX / tab->ray_spr.transformY));

		//calculate height of the sprite on screen
		tab->ray_spr.spriteHeight = abs(
		(int)(H / (tab->ray_spr.transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		tab->ray_spr.drawStartY = -tab->sprites.height / 2 + H / 2;
		if (tab->ray_spr.drawStartY < 0) tab->ray_spr.drawStartY = 0;
		tab->ray_spr.drawEndY = tab->ray_spr.spriteHeight / 2 + H / 2;
		if (tab->ray_spr.drawEndY >= H) tab->ray_spr.drawEndY = H - 1;

		//calculate width of the sprite
		tab->ray_spr.spriteWidth = abs(
		(int) (H  / (tab->ray_spr.transformY)));
		tab->ray_spr.drawStartX = -tab->sprites.width / 2 + tab->ray_spr.spriteScreenX;
		if (tab->ray_spr.drawStartX < 0) tab->ray_spr.drawStartX = 0;
		tab->ray_spr.drawEndX = tab->sprites.width / 2 + tab->ray_spr.spriteScreenX;
		if (tab->ray_spr.drawEndX >= W) tab->ray_spr.drawEndX = W - 1;

		//loop through every vertical stripe of the sprite on screen
		for (int stripe = tab->ray_spr.drawStartX; stripe < tab->ray_spr.drawEndX; stripe++) {
			tab->ray_spr.texX =
			(int)(
			256 * (stripe - (-tab->sprites.width / 2 + tab->ray_spr.spriteScreenX)) * tab->ray_spr.spriteWidth /
			tab->sprites.width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if (tab->ray_spr.transformY > 0 && stripe > 0 && stripe < W &&
					tab->ray_spr.transformY < tab->ray.z_buffer[stripe])
				for (int y = tab->ray_spr.drawStartY;
					 y < tab->ray_spr.drawEndY; y++) //for every pixel of the current stripe
				{
					tab->ray_spr.d = (y) * 256 - H * 128 + tab->ray_spr.spriteHeight *
												  128; //256 and 128 factors to avoid floats
					tab->ray_spr.texY = ((tab->ray_spr.d * tab->sprites.height) / tab->ray_spr.spriteHeight) / 256;
					tab->ray_spr.color = ft_pixel_take_spr(tab->sprites.spr_img, tab->ray_spr.texX, tab->ray_spr.texY); //get current color from the texture
					if ((int)(*tab->ray_spr.color) != 0x000000) // & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(tab, stripe, y, (int)(*tab->ray_spr.color));
//						buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
				}
		}
	}
}

void 	get_img_spr(t_tab *tab)
{
	if (!(tab->sprites.spr_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.obj, &tab->sprites.width, &tab->sprites.height)))
		exit (0);
}

void 	get_addr_spr(t_tab *tab)
{
	tab->sprites.spr_img.addr = mlx_get_data_addr\
	(tab->sprites.spr_img.img,	&tab->sprites.spr_img.bpp,\
	&tab->sprites.spr_img.line_l, &tab->sprites.spr_img.end);
}