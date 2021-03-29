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






