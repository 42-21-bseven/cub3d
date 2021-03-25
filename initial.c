#include "cub3d.h"

void ft_initial(t_tab *tab)
{
	tab->flags.floor = 0;
	tab->flags.ceil = 0;
	tab->flags.rsltn = 0;
	tab->flags.obj = 0;
	tab->flags.no = 0;
	tab->flags.so = 0;
	tab->flags.ea = 0;
	tab->flags.we = 0;
	tab->flags.map = 1;
	tab->iters.dub = 0;
	tab->check_flag = 1;
	tab->prms.clrs.floor_r = -1;
	tab->prms.clrs.floor_g = -1;
	tab->prms.clrs.floor_b = -1;
	tab->prms.clrs.ceil_r = -1;
	tab->prms.clrs.ceil_g = -1;
	tab->prms.clrs.ceil_b = -1;
	tab->prms.rsltn.x = 0;
	tab->prms.rsltn.y = 0;
	tab->prms.paths.no = NULL;
	tab->prms.paths.so = NULL;
	tab->prms.paths.ea = NULL;
	tab->prms.paths.we = NULL;
	tab->prms.paths.obj = NULL;
}