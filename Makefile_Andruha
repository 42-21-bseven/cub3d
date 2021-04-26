NAME = cub3D
C_FILES = cardinal_points.c check_square.c check_begin.c check_middle.c check_end.c\
color.c draw_texture.c error.c extra_functions.c init_struct.c main.c parser.c parser_processor.c\
press_release.c rendering.c resolution.c draw.c textures.c valid_map.c funcs.c moving.c\
draw_sprite.c screenshot.c keys.c turn_cam.c stepside.c
O_FILES = $(C_FILES:.c=.o)
HEADER = cub.h
.PHONY: all bonus clean fclean re
all: $(NAME)
$(NAME): $(O_FILES)
    @make -C ./libft
    @make -C ./minilib_static
    @make -C ./minilib_dynamic
    mv ./minilib_dynamic/libmlx.dylib ./
    gcc -g $(O_FILES) ./libft/libft.a ./minilib_static/libmlx.a libmlx.dylib -framework OpenGL -framework Appkit -o $(NAME)
%.o: %.c $(HEADER)
    @gcc -c $<
clean:
    @rm -f $(O_FILES)
    @make clean -C ./libft
    @make clean -C ./minilib_static
    @make clean -C ./minilib_dynamic
fclean: clean
    @rm -f $(NAME)
    @rm libmlx.dylib
    @make fclean -C ./libft
bonus: re
re: fclean all