#include "cub3d.h"

int rude_anal(t_tab *tab, char *str, char *right)
{
	char *head;

	head = right;
	while (*str)
	{
		right = head;
		while (*right)
		{
			if (*str == 'N' || *str == 'E' || *str == 'W' || *str == 'S')
			{
				tab->iters.dub++;
				break;
			}
			if (*str == *right)
				break ;
			right++;
		}
		if (*right == '\0' || tab->iters.dub > 1)
			return (tab->check_flag = 0);
		str++;
	}
	return (1);
}

int	map_anal(t_tab *tab)
{
	int i;
	int j;

	i = 0;
	if (tab->iters.dub == 0)
		return (tab->check_flag = 0);
	while (i < tab->lst_size)
	{
		j = 0;
		while (j < tab->lst_len)
		{
			if (tab->a.arr[i][j] == 32)
			{
				if (hard_anal(tab, i, j) == -1)
					return (-1 + (tab->check_flag = 0));
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	hard_anal(t_tab *tab, int i, int j)
{
	if (i != 0 && !(tab->a.arr[i - 1][j] == '1' || tab->a.arr[i - 1][j] == ' '
					|| tab->a.arr[i - 1][j] == '\0'))
		return (-1);
	if (i != 0 && j && !(tab->a.arr[i - 1][j + 1] == '1' ||
	tab->a.arr[i - 1][j + 1] == ' ' || tab->a.arr[i - 1][j + 1] == '\0'))
		return (-1);
	if (j != tab->lst_len && !(tab->a.arr[i][j + 1] == '1'
	|| tab->a.arr[i][j + 1] == ' ' || tab->a.arr[i][j + 1] == '\0'))
		return (-1);
	if ((i != tab->lst_size - 1) && !(tab->a.arr[i + 1][j + 1] == '1' ||
	tab->a.arr[i + 1][j + 1] == ' ' || tab->a.arr[i + 1][j + 1] == '\0'))
		return (-1);
	if (i != tab->lst_size - 1 && !(tab->a.arr[i + 1][j] == '1' ||
	tab->a.arr[i + 1][j] == ' ' || tab->a.arr[i + 1][j] == '\0'))
		return (-1);
	if (i != tab->lst_size - 1  && j != 0 && !(tab->a.arr[i + 1][j - 1] == '1'
	|| tab->a.arr[i + 1][j - 1] == ' ' || tab->a.arr[i + 1][j - 1] == '\0'))
		return (-1);
	if (j != 0 && !(tab->a.arr[i][j - 1] == '1' || tab->a.arr[i][j - 1] == ' '
					|| tab->a.arr[i][j - 1] == '\0'))
		return (-1);
	if ((j != 0 && i != 0) && !(tab->a.arr[i - 1][j - 1] == '1' ||
	tab->a.arr[i - 1][j - 1] == ' ' || tab->a.arr[i - 1][j - 1] == '\0'))
		return (-1);
}
