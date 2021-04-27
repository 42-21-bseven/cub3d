#include "./cub3d.h"

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

void 	get_img_spr(t_tab *tab)
{
	if (!(tab->sprites.spr_img.img = mlx_xpm_file_to_image(tab->data.mlx,\
	tab->prms.paths.obj, &tab->ray_spr.spriteWidth, &tab->ray_spr.spriteHeight)))
		exit (0);
}

void 	get_addr_spr(t_tab *tab)
{
	tab->sprites.spr_img.addr = mlx_get_data_addr\
	(tab->sprites.spr_img.img,	&tab->sprites.spr_img.bpp,\
	&tab->sprites.spr_img.line_l, &tab->sprites.spr_img.end);
}