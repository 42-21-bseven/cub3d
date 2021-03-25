#include "cub3d.h"

void  cut_space(char **str)
{
	int    i;
	int    j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if (j != i)
			(*str)[j] = (*str)[i];
		if ((*str)[i] == 32)
		{
			while ((*str)[i + 1] == 32)
				i++;
		}
		j++;
		i++;
	}
	(*str)[j] = '\0';
}

int snd_lit_check(t_tab *tab, char *str)
{
	if (*str == 'N' && *(str + 1) == 'O')
		return (check_paths(tab, tab->prms.paths.no = get_path(str + 2),
							&tab->flags.no));
	if (*str == 'S' && *(str + 1) == 'O')
		return (check_paths(tab, tab->prms.paths.so = get_path(str + 2),
							&tab->flags.so));
	if (*str == 'E' && *(str + 1) == 'A')
		return (check_paths(tab, tab->prms.paths.ea = get_path(str + 2),
							&tab->flags.ea));
	if (*str == 'W' && *(str + 1) == 'E')
		return (check_paths(tab, tab->prms.paths.we = get_path(str + 2),
							&tab->flags.we));
	if (*str == 'S' && *(str + 1) == 32)
		return (check_paths(tab, tab->prms.paths.obj = get_path(str + 1),
							&tab->flags.obj));
	return (0);
}

int not_comma_check (char **str)
{
	while (**str && !(ft_isdigit(**str)))
	{
		if ((*(*str)++) == ',')
			return (0);
	}
	return (1);
}

int range_clr(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	return (0);
}