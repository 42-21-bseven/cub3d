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
