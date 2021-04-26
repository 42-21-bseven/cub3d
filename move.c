#include "./cub3d.h"

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
	printf("KEY %d\n", key);
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

void 	for_rotate_right(t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.025;
	//both camera direction and camera plane must be rotated
	tab->ray.old_dir_x = tab->pers.dir_x;
	tab->pers.dir_x = \
		tab->pers.dir_x * cos(-rotSpeed) - tab->pers.dir_y * sin(-rotSpeed);
	tab->pers.dir_y = \
		tab->ray.old_dir_x * sin(-rotSpeed) + tab->pers.dir_y * cos(-rotSpeed);
	tab->ray.old_plane_x = tab->pers.plane_x;
	tab->pers.plane_x = \
		tab->pers.plane_x * cos(-rotSpeed) - tab->pers.plane_y * sin(-rotSpeed);
	tab->pers.plane_y = tab->ray.old_plane_x \
		* sin(-rotSpeed) + tab->pers.plane_y * cos(-rotSpeed);
}

void 	for_rotate_left(t_tab *tab)
{
	double rotSpeed;

	rotSpeed = 0.025;
	//both camera direction and camera plane must be rotated
	tab->ray.old_dir_x = tab->pers.dir_x;
	tab->pers.dir_x = \
		tab->pers.dir_x * cos(rotSpeed) - tab->pers.dir_y * sin(rotSpeed);
	tab->pers.dir_y = \
		tab->ray.old_dir_x * sin(rotSpeed) + tab->pers.dir_y * cos(rotSpeed);
	tab->ray.old_plane_x = tab->pers.plane_x;
	tab->pers.plane_x = \
		tab->pers.plane_x * cos(rotSpeed) - tab->pers.plane_y * sin(rotSpeed);
	tab->pers.plane_y = \
		tab->ray.old_plane_x * sin(rotSpeed) + tab->pers.plane_y * cos(rotSpeed);
}

int		ft_move(t_tab *tab)
{
//	printf("KEY %d\n", key);
	if(tab->move.up)
		for_move_up(tab);
	//move backwards if no wall behind you
	if(tab->move.down)
		for_move_down(tab);
	//rotate to the right
	if (tab->move.right)
		for_rotate_right(tab);
	//rotate to the left
	if (tab->move.left)
		for_rotate_left(tab);
	if (tab->move.scroll_left)
		for_scroll_left(tab);
	if (tab->move.scroll_right)
		for_scroll_right(tab);
	draw_floor_ceil(tab);
	draw(tab);
	return (0);
}