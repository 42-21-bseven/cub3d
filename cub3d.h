#ifndef CUB3D_H
# define CUB3D_H
# include "libft_cub3d/libft.h"
# include "gnl_cub3d/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include "minilibx/mlx.h"
//#include "./minilibx_opengl_20191021/mlx.h"
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
//# define rot_speed (0.05)

typedef struct	s_spr
{
	double x;
	double y;
	double dist;
}				t_spr;

typedef struct	s_img
{
	void	*img;
	void 	*addr;
	int 	line_l;
	int		bpp;
	int		end;
}				t_img;

typedef struct	s_wall_info
{
	t_img	wall_img;
	int 	width;
	int		height;
}				t_wall_info;

typedef struct 	s_sprites
{
	int count_sprites;
	int height;
	int width;
	t_img spr_img;
	t_spr *arr_spr;
}				t_sprites;

typedef struct 	s_ray_spr
{
	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
	int spriteScreenX;
	int spriteHeight;
	int drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
	int texX;
	int d;
	int texY;
	unsigned int	*color;
}				t_ray_spr;

typedef struct	s_walls_tex
{
	t_wall_info no;
	t_wall_info so;
	t_wall_info ea;
	t_wall_info we;
}				t_walls_tex;

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
	double		camera_x; // = 2 * x / (double)w - 1; //x-coordinate in camera space
	double		ray_dir_x; // = dir_x + plane_x*camera_x;
	double		ray_dir_y; // = dir_y + plane_y*camera_x;
	int			map_x; // = int(pos_x);
	int			map_y; // = int(pos_y);
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x; // = std::abs(1 / ray_dir_x);
	double		delta_dist_y; // = std::abs(1 / ray_dir_y);
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	unsigned int	*color;
	int			hit; // = 0; //was there a wall hit?
	int			side; //was a NS or a EW wall hit?
	int			line_height; // = (int)(h / perp_wall_dist);
	int			draw_start; // = -line_height / 2 + h / 2;
	int			draw_end; // = line_height / 2 + h / 2;
	int			tex_num; // = worldMap[map_x][map_y] - 1; //1 subtracted from it so that texture 0 can be used!
	double		wall_x; //where exactly the wall was hit
	int			tex_x; // = int(wall_x * double(texWidth));
	double		step; // = 1.0 * texHeight / line_height;
	double		tex_pos; // = (draw_start - h / 2 + line_height / 2) * step;
	int			tex_y; // = (int)tex_pos & (texHeight - 1);
	double		frame_time; //= (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
	double		move_speed; // = frame_time * 5.0; //the constant value is in squares/second
	double		rot_speed; // = frame_time * 3.0; //the constant value is in radians/second
	double		old_dir_x; // = dir_x;
	double		old_plane_x; // = plane_x;
	double 		*z_buffer;
}				t_ray;

typedef struct	s_pers
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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
	int 	x;
	int 	y;
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
	t_walls_tex walls_tex;
	t_sprites sprites;
	t_ray_spr ray_spr;
	t_img *img;
	int 			screen;
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

void 	get_addr(t_tab *tab);
void 	get_img(t_tab *tab);

void		draw(t_tab *tab);
void	color_convert(t_tab *tab);
void	draw_floor_ceil(t_tab *tab);
unsigned int  *ft_pixel_take(t_wall_info tex, int x, int y);

void	pers_orient(t_tab *tab);
void	pers_orient_2(t_tab *tab);

int		ft_move(t_tab *tab);
int		ft_press(int key, t_tab *tab);
int		ft_unpress(int key, t_tab *tab);
void 	for_move_up(t_tab *tab);
void 	for_move_down(t_tab *tab);
void	for_scroll_right(t_tab *tab);
void	for_scroll_left(t_tab *tab);
void 	for_rotate_right(t_tab *tab);
void 	for_rotate_left(t_tab *tab);

void	initial_sprites(t_tab *tab);
void 	bubble_sort(t_spr *tab, int count);
void 	calc_distance(t_tab *tab);

unsigned int  *ft_pixel_take_spr(t_img spr_img, int x, int y);
void            my_mlx_pixel_put(t_tab *tab, int x, int y, int color);
void 	draw_sprites(t_tab *tab);
void 	get_img_spr(t_tab *tab);
void 	get_addr_spr(t_tab *tab);

void 	for_mlx_initial_window(t_tab *tab);
void 	for_mlx_loop_hook(t_tab *tab);
void 	for_sprite_draw(t_tab *tab);

void 		calc_pos_and_direct(t_tab *tab, int x);
void 		calc_len_ray(t_tab *tab);
void 		calc_step_and_side_dist(t_tab *tab);
void 		perf_dda(t_tab *tab);


void 	fr_screenshot(t_tab *tab);

int 	ft_close(void);

#endif

