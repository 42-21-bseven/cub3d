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

void	pers_orient(t_tab *tab, int i, int j)
{

	if (tab->a.arr[i][j] == 'N')
	{
		tab->pers.dirX = -1.0;
		tab->pers.dirY = 0.0;
		tab->pers.planeX = 0.00;
		tab->pers.planeY = 0.66;
	}
	if (tab->a.arr[i][j] == 'S')
	{
		tab->pers.dirX = 1.0;
		tab->pers.dirY = 0.0;
		tab->pers.planeX = 0.00;
		tab->pers.planeY = -0.66;
	}
}

void	pers_orient_2(t_tab *tab, int i, int j)
{
	if (tab->a.arr[i][j] == 'E')
	{
		tab->pers.dirX = 0.0;
		tab->pers.dirY = 1.0;
		tab->pers.planeX = 0.66;
		tab->pers.planeY = 0.00;
	}
	if (tab->a.arr[i][j] == 'W')
	{
		tab->pers.dirX = 0.0;
		tab->pers.dirY = -1.0;
		tab->pers.planeX = -0.66;
		tab->pers.planeY = 0.00;
	}
}


