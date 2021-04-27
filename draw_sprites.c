#include "./cub3d.h"

void 	calc_distance(t_tab *tab)
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

void 	translate_and_transform(t_tab *tab, int i)
{
	//translate sprite position to relative to camera
	tab->ray_spr.spriteX = tab->sprites.arr_spr[i].x - tab->pers.pos_x + 0.5;
	tab->ray_spr.spriteY = tab->sprites.arr_spr[i].y - tab->pers.pos_y + 0.5;

	//transform sprite with the inverse camera matrix
	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	tab->ray_spr.invDet = 1.0 / (tab->pers.plane_x * tab->pers.dir_y - tab->pers.dir_x * tab->pers.plane_y);
	//required for correct matrix multiplication

	tab->ray_spr.transformX = tab->ray_spr.invDet * (tab->pers.dir_y * tab->ray_spr.spriteX - tab->pers.dir_x * tab->ray_spr.spriteY);
	tab->ray_spr.transformY = tab->ray_spr.invDet * (-tab->pers.plane_y * tab->ray_spr.spriteX + tab->pers.plane_x * tab->ray_spr.spriteY);
	tab->ray_spr.spriteScreenX = (int)((W / 2) * (1 + tab->ray_spr.transformX / tab->ray_spr.transformY));
	//this is actually the depth inside the screen, that what Z is in 3D

}

void 	calc_line_texture_sprite(t_tab *tab)
{
	//calculate height of the sprite on screen
	tab->ray_spr.spriteHeight = abs((int)(H / (tab->ray_spr.transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	tab->ray_spr.drawStartY = -tab->ray_spr.spriteHeight / 2 + H / 2;
	if (tab->ray_spr.drawStartY < 0)
		tab->ray_spr.drawStartY = 0;
	tab->ray_spr.drawEndY = tab->ray_spr.spriteHeight / 2 + H / 2;
	if (tab->ray_spr.drawEndY >= H)
		tab->ray_spr.drawEndY = H;

	//calculate width of the sprite
	tab->ray_spr.spriteWidth = abs((int) (W / (tab->ray_spr.transformY)));
	tab->ray_spr.drawStartX = -tab->ray_spr.spriteWidth / 2 + tab->ray_spr.spriteScreenX;
	if (tab->ray_spr.drawStartX < 0)
		tab->ray_spr.drawStartX = 0;
	tab->ray_spr.drawEndX = tab->ray_spr.spriteWidth / 2 + tab->ray_spr.spriteScreenX;
	if (tab->ray_spr.drawEndX >= W)
		tab->ray_spr.drawEndX = W;

}

void 		perf_dda_sprite(t_tab *tab)
{
	//loop through every vertical stripe of the sprite on screen
//		for (int stripe = tab->ray_spr.drawStartX; stripe < tab->ray_spr.drawEndX; stripe++)
	int stripe;
	int y;

	stripe = tab->ray_spr.drawStartX;
	y = tab->ray_spr.drawStartY;
	while (stripe < tab->ray_spr.drawEndX)
	{
		tab->ray_spr.texX =
				(int)(256 * (stripe - (-tab->ray_spr.spriteWidth / 2 + tab->ray_spr.spriteScreenX)) * texWidth / tab->ray_spr.spriteWidth) / 256;
		//the conditions in the if are:
		//1) it's in front of camera plane so you don't see things behind you
		//2) it's on the screen (left)
		//3) it's on the screen (right)
		//4) ZBuffer, with perpendicular distance
		if (tab->ray_spr.transformY > 0 && stripe >= 0 && stripe < W &&
			tab->ray_spr.transformY < tab->ray.z_buffer[stripe])
			y = tab->ray_spr.drawStartY;
//				for (int y = tab->ray_spr.drawStartY; y < tab->ray_spr.drawEndY; y++) //for every pixel of the current stripe
		while (y < tab->ray_spr.drawEndY)
		{
			tab->ray_spr.d = (y) * 256 - H * 128 + tab->ray_spr.spriteHeight * 128;
			//256 and 128 factors to avoid floats
			tab->ray_spr.texY = ((tab->ray_spr.d * texHeight) / tab->ray_spr.spriteHeight) / 256;
			tab->ray_spr.color = ft_pixel_take_spr(tab->sprites.spr_img, tab->ray_spr.texX, tab->ray_spr.texY); //get current color from the texture
			if ((int)(*tab->ray_spr.color) != 0x000000) // & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(tab, stripe, y, (int)(*tab->ray_spr.color));
			y++;
//						buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
		}
		stripe++;
	}
}