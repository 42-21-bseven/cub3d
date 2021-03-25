#ifndef CUB3D_H
# define CUB3D_H
# include "libft_cub3d/libft.h"
# include "gnl_cub3d/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>

typedef struct      s_clrs
{
    int floor_r;
    int floor_g;
    int floor_b;
    int ceil_r;
    int ceil_g;
    int ceil_b;
}                   t_clrs;

typedef struct      s_rsltn
{
    int x;
    int y;
}                   t_rsltn;

typedef struct      s_paths
{
    char *no;
    char *so;
    char *ea;
    char *we;
    char *obj;
}                   t_paths;

typedef struct 		s_prms
{
	t_clrs clrs;
	t_rsltn rsltn;
	t_paths paths;
}					t_prms;

typedef struct 		s_flags
{
	int floor;
	int ceil;
	int rsltn;
	int no;
	int so;
	int ea;
	int we;
	int obj;
	int map;
}					t_flags;

typedef struct 		s_iters
{
	int i;
	int j;
	int k;
	int n;
	int flag;
	int dub;
}					t_iters;

typedef struct 		s_array
{
	char **arr;
}					t_array;

typedef struct      s_tab
{
    t_prms prms;
    t_flags flags;
    t_iters iters;
    int check_flag;
    int lst_len;
    int lst_size;
    t_array a;
}                   t_tab;

void  cut_space(char **str);
int parse_param (t_tab *tab, char *line);
int parse_rsltn (t_tab *tab, char **str);
int check_place (t_tab *tab, char **str);
int parse_clrs_c (t_tab *tab, char **str);
int parse_clrs_f (t_tab *tab, char **str);

int snd_lit_check(t_tab *tab, char *str);
int not_comma_check (char **str);
int range_clr(int r, int g, int b);

char *get_path(char *line);
int check_paths (t_tab *tab, char *str, int *flag);

int parse_map(t_tab *tab, char *str, t_list **map);
int search_map(t_tab *tab, char *str);
void how_list_size(t_tab *tab, t_list *map);
int mem_for_map(t_tab *tab);
void map_to_array(t_tab *tab, t_list *map);

void str_to_str(void *srcs, char *dest, int len);

int rude_anal(t_tab *tab, char *str, char *right);
int	map_anal(t_tab *tab);
int	hard_anal(t_tab *tab, int i, int j);

void ft_initial(t_tab *tab);
void free_list(t_list **head);
void free_struct(t_tab *tab);

#endif