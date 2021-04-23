#include "cub3d.h"

void str_to_str(void *srcs, char *dest, int len)
{
	char	*temp;
	int 	i;

	temp = (char *)srcs;
	i = 0;
	while (i < len)
	{
		if (i > 0 && temp && *temp)
			dest[i] = *temp++;
		else
			dest[i] = ' ';
		i++;
	}
}

void	pers_orient(t_tab *tab)
{

	if (tab->pers.orient == 'N')
	{
		tab->pers.dir_x = -1.0;
		tab->pers.dir_y = 0.0;
		tab->pers.plane_x = 0.00;
		tab->pers.plane_y = 0.66;
	}
	if (tab->pers.orient == 'S')
	{
		tab->pers.dir_x = 1.0;
		tab->pers.dir_y = 0.0;
		tab->pers.plane_x = 0.00;
		tab->pers.plane_y = -0.66;
	}
}

void	pers_orient_2(t_tab *tab)
{
	if (tab->pers.orient == 'E')
	{
		tab->pers.dir_x = 0.0;
		tab->pers.dir_y = 1.0;
		tab->pers.plane_x = 0.66;
		tab->pers.plane_y = 0.00;
	}
	if (tab->pers.orient == 'W')
	{
		tab->pers.dir_x = 0.0;
		tab->pers.dir_y = -1.0;
		tab->pers.plane_x = -0.66;
		tab->pers.plane_y = 0.00;
	}
}


