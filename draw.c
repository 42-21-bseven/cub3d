#include "./cub3d.h"

void	draw_floor_ceil(t_tab *tab)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < tab->prms.rsltn.y / 2)
	{
		while (x < tab->prms.rsltn.x)
			my_mlx_pixel_put(tab, x++, y, tab->prms.clrs.ceil_res);
		x = 0;
		y++;
	}
	while (y < tab->prms.rsltn.y)
	{
		while (x < tab->prms.rsltn.x)
			my_mlx_pixel_put(tab, x++, y, tab->prms.clrs.floor_res);
		x = 0;
		y++;
	}
}

void		color_convert(t_tab *tab)
{
	tab->prms.clrs.floor_res = (tab->prms.clrs.floor_r << 16 | \
	tab->prms.clrs.floor_g << 8 | tab->prms.clrs.floor_b);
	tab->prms.clrs.ceil_res = (tab->prms.clrs.ceil_r << 16 | \
	tab->prms.clrs.ceil_g << 8 | tab->prms.clrs.ceil_b);
}

void 		calc_pos_and_direct(t_tab *tab, int x)
{
	//calculate ray position and direction
	tab->ray.camera_x = 2 * x / (double)W - 1; //x-coordinate in camera space
	tab->ray.ray_dir_x = tab->pers.dir_x + tab->pers.plane_x * tab->ray.camera_x;
	tab->ray.ray_dir_y = tab->pers.dir_y + tab->pers.plane_y * tab->ray.camera_x;

	//which box of the map we're in
	tab->ray.map_x = (int)tab->pers.pos_x;
	tab->ray.map_y = (int)tab->pers.pos_y;
}

void 		calc_len_ray(t_tab *tab)
{
	//length of ray from one x or y-side to next x or y-side
	if (tab->ray.ray_dir_y == 0)
	{
		tab->ray.delta_dist_x = 0;
	}
	else
	{
		if (tab->ray.ray_dir_x == 0)
			tab->ray.delta_dist_x = 1;
		else
			tab->ray.delta_dist_x = fabs(1 / tab->ray.ray_dir_x);
	}
	if (tab->ray.ray_dir_x == 0)
	{
		tab->ray.delta_dist_y = 0;
	}
	else
	{
		if (tab->ray.ray_dir_y == 0)
			tab->ray.delta_dist_y = 1;
		else
			tab->ray.delta_dist_y = fabs(1 / tab->ray.ray_dir_y);
	}
	tab->ray.hit = 0; //was there a wall hit?
	tab->ray.side_dist_x = 0;
}

void 		calc_step_and_side_dist(t_tab *tab)
{
	//calculate step and initial sideDist
	if(tab->ray.ray_dir_x < 0)
	{
		tab->ray.step_x = -1;
		tab->ray.side_dist_x = \
			(tab->pers.pos_x - tab->ray.map_x) * tab->ray.delta_dist_x;
	}
	else
	{
		tab->ray.step_x = 1;
		tab->ray.side_dist_x = \
			(tab->ray.map_x + 1.0 - tab->pers.pos_x) * tab->ray.delta_dist_x;
	}
	if(tab->ray.ray_dir_y < 0)
	{
		tab->ray.step_y = -1;
		tab->ray.side_dist_y = \
			(tab->pers.pos_y - tab->ray.map_y) * tab->ray.delta_dist_y;
	}
	else
	{
		tab->ray.step_y = 1;
		tab->ray.side_dist_y = \
			(tab->ray.map_y + 1.0 - tab->pers.pos_y) * tab->ray.delta_dist_y;
	}
}

void 		perf_dda(t_tab *tab)
{
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
}

void 		calc_perpend_ray(t_tab *tab)
{
	//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
	if (tab->ray.side == 0)
	{
		tab->ray.perp_wall_dist = (tab->ray.map_x - \
			tab->pers.pos_x + (1.0 - tab->ray.step_x) / 2) / tab->ray.ray_dir_x;
//			printf("map_x - %d, pos_x - %f, dir_x - %f, perp_wall_dist - %f\n", tab->ray.map_x, tab->character.pos_x, tab->ray.ray_dir_x, tab->ray.perp_wall_dist);
	}
	else
	{
		tab->ray.perp_wall_dist = (tab->ray.map_y - \
			tab->pers.pos_y + (1.0 - tab->ray.step_y) / 2) / tab->ray.ray_dir_y;
//			printf("map_y - %d, pos_y - %f, dir_y - %f, perp_wall_dist - %f\n", tab->ray.map_y, tab->character.pos_y, tab->ray.ray_dir_y, tab->ray.perp_wall_dist);
	}
}

void		calc_line_texture_draw(t_tab *tab)
{
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
	if(tab->ray.side == 0)
		tab->ray.wall_x = tab->pers.pos_y + tab->ray.perp_wall_dist * tab->ray.ray_dir_y;
	else
		tab->ray.wall_x = tab->pers.pos_x + tab->ray.perp_wall_dist * tab->ray.ray_dir_x;
	tab->ray.wall_x -= floor((tab->ray.wall_x));

	//x coordinate on the texture
	tab->ray.tex_x = (int)(tab->ray.wall_x * (double)texWidth);
	if(tab->ray.side == 0 && tab->ray.ray_dir_x > 0)
		tab->ray.tex_x = texWidth - tab->ray.tex_x - 1;
	if(tab->ray.side == 1 && tab->ray.ray_dir_y < 0)
		tab->ray.tex_x = texWidth - tab->ray.tex_x - 1;
}

void 		calc_size_texture(t_tab *tab, int x)
{
	int y;

	y = tab->ray.draw_start;
	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	tab->ray.step = 1.0 * texHeight / tab->ray.line_height;
	// Starting texture coordinate
	tab->ray.tex_pos = \
		(tab->ray.draw_start - H / 2.0 + tab->ray.line_height / 2.0) * tab->ray.step;
	while (y < tab->ray.draw_end)
	{			t_wall_info tex;
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
		tab->ray.color = ft_pixel_take(tex, tab->ray.tex_x, tab->ray.tex_y);//0xff00ff; // (tab->ray.color >> 1) & 8355711;
//			printf("x - %d, y - %d\n", x, y);
		my_mlx_pixel_put(tab, x, y, (int)(*tab->ray.color));
		y++;
	}
}

void		draw(t_tab *tab)
{
	int x;

	x = -1;
	//	W = 800;
	//	H = 600;
	draw_floor_ceil(tab);
	while (++x < W)
	{

		calc_pos_and_direct(tab, x);

		calc_len_ray(tab);

//		tab->ray.delta_dist_x = fabs(1 / tab->ray.ray_dir_x);
//		tab->ray.delta_dist_y = fabs(1 / tab->ray.ray_dir_y);

		calc_step_and_side_dist(tab);


		perf_dda(tab);

		calc_perpend_ray(tab);


		calc_line_texture_draw(tab);


		calc_size_texture(tab, x);

		tab->ray.z_buffer[x] = tab->ray.perp_wall_dist; //perpendicular distance is used
	}

	calc_distance(tab);

	draw_sprites(tab);
	if(tab->screen != 1)
	{
		mlx_put_image_to_window
		(tab->data.mlx, tab->data.win, tab->data.img, 0, 0);
		mlx_destroy_image(tab->data.mlx, tab->data.img);
		tab->data.img = mlx_new_image(tab->data.mlx, W, H);
		tab->data.addr = mlx_get_data_addr(tab->data.img, \
    	&tab->data.bits_per_pixel, &tab->data.line_length, &tab->data.endian);
	}
}