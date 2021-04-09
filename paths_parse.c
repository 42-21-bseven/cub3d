#include "cub3d.h"

char *get_path(char *line)
{
	char *tmp;
	char *end;
	char *head;

	tmp = NULL;
	if (*line != 32)
		return (0);
	line++;
	end = line;
	while (*end)
		end++;
	*end = '\0';
	tmp = calloc((ft_strlen(line) + 1), sizeof (char));
	head = tmp;
	while (*line)
		*tmp++ = *line++;
	*tmp = '\0';
	return (head);
}

int check_paths (t_tab *tab, char *str, int *flag)
{
	char *head_path;
	int fd;

	fd = 0;
	head_path = str;
	if (*flag == 1)
		return (put_error("\nERROR!\nDuplicate Path.\n"));
	while (str && *str)
		str++;
	if (head_path && *(--str) == 'm' && *(--str) == 'p' && *(--str) == 'x' && *(--str) == '.')
		if ((fd = open(head_path, O_RDONLY)) > 0)
		{
			close(fd);
			return (*flag = 1);
		}
	close(fd);
	return (tab->check_flag = put_error("\nERROR!\nWrong Path.\n"));
}