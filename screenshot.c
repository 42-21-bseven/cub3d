#include "./cub3d.h"

void 	header_for_bmp(int fd, int file_size)
{
	unsigned char	header[14];

	ft_bzero(header, 14);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

void 	bmp_info(int fd, t_tab *tab)
{
	unsigned char	bmp_info[40];

	ft_bzero(bmp_info, 40);
	bmp_info[0] = (unsigned char)(40);
	bmp_info[4] = (unsigned char)(tab->prms.rsltn.x);
	bmp_info[5] = (unsigned char)(tab->prms.rsltn.x >> 8);
	bmp_info[6] = (unsigned char)(tab->prms.rsltn.x >> 16);
	bmp_info[7] = (unsigned char)(tab->prms.rsltn.x >> 24);
	bmp_info[8] = (unsigned char)(tab->prms.rsltn.y);
	bmp_info[9] = (unsigned char)(tab->prms.rsltn.y >> 8);
	bmp_info[10] = (unsigned char)(tab->prms.rsltn.y >> 16);
	bmp_info[11] = (unsigned char)(tab->prms.rsltn.y >> 24);
	bmp_info[12] = (unsigned char)(1);
	bmp_info[14] = (unsigned char)(32);
	write(fd, bmp_info, 14);
}

void 	fr_screenshot(t_tab *tab)
{
	int fd;
	int	file_size;
	int height;
	int len_line;

	fd = open("screenshot.bpm", O_CREAT | O_WRONLY | O_TRUNC, 0655);
	if (fd < 0)
	{
		put_error("\nERROR!\nInvalid Screenshot File.\n");
	}
	draw(tab);
	file_size = 14 + 40 + (4 * tab->prms.rsltn.y * tab->prms.rsltn.x);
	header_for_bmp(fd, file_size);
	bmp_info(fd, tab);
	height = tab->prms.rsltn.y;
	len_line = tab->prms.rsltn.x * tab->img->bpp / 8;
	while (height > -1)
	{
		write(fd, (unsigned char *)(tab->img->addr + height * tab->img->line_l), len_line);
		height--;
	}
	close(fd);
}