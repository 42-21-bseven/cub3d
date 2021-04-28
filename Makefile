# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bseven <bseven@student.21-school.>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 03:54:32 by bseven            #+#    #+#              #
#    Updated: 2021/04/28 03:54:36 by bseven           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =	addition_fun.c \
		cub.c \
		cub_utils.c \
		draw.c \
		draw_get_textures.c \
		draw_post_dda.c \
		draw_pre_dda.c \
		draw_sprites.c \
		draw_sprites_utils.c \
		for_move.c \
		initial.c \
		initial_mlx.c \
		map_anal.c \
		move.c \
		my_pixel.c \
		parse_map.c \
		parse_map_add.c \
		parse_params.c \
		parse_params_add.c \
		parse_paths.c \
		screenshot.c \
		./gnl_cub3d/get_next_line.c \
		./gnl_cub3d/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

HEAD = cub.h

all: $(NAME)

$(NAME): $(OBJS)
	@make bonus -C ./libft_cub3d
	@make -C ./minilibx_opengl_20191021
	@make -C ./minilibx_mms_20200219
	mv ./minilibx_mms_20200219/libmlx.dylib ./
	gcc -g $(OBJS) ./libft_cub3d/libft.a ./minilibx_opengl_20191021/libmlx.a libmlx.dylib -framework OpenGL -framework Appkit -o $(NAME)

%.o: %.c $(HEAD)
	@gcc -c $<

clean:
	@rm -f $(OBJS)
	@make fclean -C ./libft_cub3d
	@make clean -C ./minilibx_opengl_20191021
	@make clean -C ./minilibx_mms_20200219

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib

bonus: re

re: fclean all

.PHONY: all bonus clean fclean re
