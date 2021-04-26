#include "cub3d.h"

void 	for_move_up(t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.085;
	if(tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_x * rotSpeed * 1.5)]\
		[(int)(tab->pers.pos_y)] == '0') // && tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '2')
		tab->pers.pos_x += tab->pers.dir_x * rotSpeed;
	if(tab->a.arr[(int)(tab->pers.pos_x)]\
		[(int)(tab->pers.pos_y + tab->pers.dir_y * rotSpeed)] == '0') // && tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y + tab->pers.dir_y * rotSpeed)] != '2')
		tab->pers.pos_y += tab->pers.dir_y * rotSpeed;
	write(1, "test\n", 5);
}

void 	for_move_down(t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.085;
	if(tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_x * rotSpeed * 1.5)]\
		[(int)(tab->pers.pos_y)] == '0') // && tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_x * rotSpeed)][(int)(tab->pers.pos_y)] != '2')
		tab->pers.pos_x -= tab->pers.dir_x * rotSpeed;
	if(tab->a.arr[(int)(tab->pers.pos_x)]\
		[(int)(tab->pers.pos_y - tab->pers.dir_y * rotSpeed)] == '0') // && tab->a.arr[(int)(tab->pers.pos_x)][(int)(tab->pers.pos_y - tab->pers.dir_y * rotSpeed)] != '2')
		tab->pers.pos_y -= tab->pers.dir_y * rotSpeed;
	write(1, "test2\n", 6);
}

void	for_scroll_right(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x + tab->pers.dir_y * 0.17)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x += tab->pers.dir_y * 0.06;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y - tab->pers.dir_x * 0.17)] == '0')
	{
		tab->pers.pos_y -= tab->pers.dir_x * 0.06;
	}
}

void	for_scroll_left(t_tab *tab)
{
	if (tab->a.arr[(int)(tab->pers.pos_x - tab->pers.dir_y * 0.17)]
		[(int)(tab->pers.pos_y)] == '0')
	{
		tab->pers.pos_x -= tab->pers.dir_y * 0.06;
	}
	if (tab->a.arr[(int)(tab->pers.pos_x)]
		[(int)(tab->pers.pos_y + tab->pers.dir_x * 0.17)] == '0')
	{
		tab->pers.pos_y += tab->pers.dir_x * 0.06;
	}
}