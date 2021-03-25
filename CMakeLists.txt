cmake_minimum_required(VERSION 3.17)
project(cub C)

set(CMAKE_C_STANDARD 99)
#SET(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
file(GLOB SOURCE_FILES *.c ./gnl_cub3d/*.c ./gnl_cub3d/*.h ./libft_cub3d/*.c ./libft_cub3d/*.h)
add_executable(cube3D ${SOURCE_FILES} initial.c)
#add_executable(GLOB SOURCE_FILE cub ./main.c cub3d.h ./gnl_cub3d/get_next_line.h ./libft_cub3d/libft.h ./libft_cub3d/*.c ./gnl_cub3d/*.c)