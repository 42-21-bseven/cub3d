#ifndef CUB3D_H
# define CUB3D_H
# include "libft_cub3d/libft.h"
# include "gnl_cub3d/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include "minilibx/mlx.h"
# include <math.h>
# define W tab->prms.rsltn.x
# define H tab->prms.rsltn.y
# define WORLDMAP tab.a.arr
# define WWORLDMAP tab->a.arr
# define screenWidth 640
# define screenHeight 480
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24
//# define rotSpeed (0.05)

typedef struct s_move
{
	int up;
	int down;
	int right;
	int left;
	int scroll_right;
	int scroll_left;
	int close;
}				t_move;

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*win;
}				t_data;

typedef struct	s_ray
{
	double		cameraX; // = 2 * x / (double)w - 1; //x-coordinate in camera space
	double		rayDirX; // = dirX + planeX*cameraX;
	double		rayDirY; // = dirY + planeY*cameraX;
	int			mapX; // = int(posX);
	int			mapY; // = int(posY);
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX; // = std::abs(1 / rayDirX);
	double		deltaDistY; // = std::abs(1 / rayDirY);
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			color;
	int			hit; // = 0; //was there a wall hit?
	int			side; //was a NS or a EW wall hit?
	int			lineHeight; // = (int)(h / perpWallDist);
	int			drawStart; // = -lineHeight / 2 + h / 2;
	int			drawEnd; // = lineHeight / 2 + h / 2;
	int			texNum; // = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
	double		wallX; //where exactly the wall was hit
	int			texX; // = int(wallX * double(texWidth));
	double		step; // = 1.0 * texHeight / lineHeight;
	double		texPos; // = (drawStart - h / 2 + lineHeight / 2) * step;
	int			texY; // = (int)texPos & (texHeight - 1);
	double		frameTime; //= (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	double		moveSpeed; // = frameTime * 5.0; //the constant value is in squares/second
	double		rotSpeed; // = frameTime * 3.0; //the constant value is in radians/second
	double		oldDirX; // = dirX;
	double		oldPlaneX; // = planeX;
}				t_ray;

typedef struct	s_pers
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	char		orient;
}				t_pers;

typedef struct		s_clrs
{
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		floor_res;
	int		ceil_r;
	int		ceil_g;
	int		ceil_b;
	int		ceil_res;
}					t_clrs;

typedef struct		s_rsltn
{
	int		x;
	int		y;
}					t_rsltn;

typedef struct		s_paths
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*obj;
}					t_paths;

typedef struct		s_prms
{
	t_clrs	clrs;
	t_rsltn	rsltn;
	t_paths	paths;
}					t_prms;

typedef struct		s_flags
{
	int		floor;
	int		ceil;
	int		rsltn;
	int		no;
	int		so;
	int		ea;
	int		we;
	int		obj;
	int		map;
}					t_flags;

typedef struct		s_iters
{
	int		i;
	int		j;
	int		k;
	int		n;
	int		flag;
	int		dub;
}					t_iters;

typedef struct		s_array
{
	char	**arr;
}					t_array;

typedef struct		s_tab
{
	t_prms	prms;
	t_flags	flags;
	t_iters	iters;
	int		check_flag;
	int		lst_len;
	int		lst_size;
	t_array	a;
	t_data data;
	t_ray ray;
	t_pers pers;
	t_move move;
}					t_tab;

void				cut_space(char **str);
int					parse_param (t_tab *tab, char *line);
int					parse_rsltn (t_tab *tab, char **str);
int					check_place (t_tab *tab, char **str);
int					parse_clrs_c (t_tab *tab, char **str);
int					parse_clrs_f (t_tab *tab, char **str);

int					snd_lit_check(t_tab *tab, char *str);
int					char_check (char **str);
int					range_clr(int r, int g, int b);
int					put_error(char *str);

char				*get_path(char *line);
int					check_paths (t_tab *tab, char *str, int *flag);

int					parse_map(t_tab *tab, char *str, t_list **map);
int					search_map(t_tab *tab, char *str);
void				how_list_size(t_tab *tab, t_list *map);
int					mem_for_map(t_tab *tab);
void				map_to_array(t_tab *tab, t_list *map);

void				str_to_str(void *srcs, char *dest, int len);

int					rude_anal(t_tab *tab, char *str, char *right);
int					map_anal(t_tab *tab);
int					hard_anal(t_tab *tab, int i, int j);

void				initial_parse(t_tab *tab);
void				initial_move(t_tab *tab);
void				free_list(t_list **head);
void				free_struct(t_tab *tab);


int		draw(t_tab *tab);
void	color_convert(t_tab *tab);
void	draw_floor_ceil(t_tab *tab);
void	pers_orient(t_tab *tab);
void	pers_orient_2(t_tab *tab);
void	for_scroll_right(t_tab *tab);
void	for_scroll_left(t_tab *tab);

#endif

