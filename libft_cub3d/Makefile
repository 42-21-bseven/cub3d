# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bseven <bseven@student.21-school.>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 01:31:07 by bseven            #+#    #+#              #
#    Updated: 2020/11/18 21:07:17 by bseven           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

LIB = ar rc

HEADER = libft.h

FLAGS = -Wall -Werror -Wextra

NAME = libft.a

RM = rm -f

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memmove.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

B_OBJS = $(B_SRCS:.c=.o)

.c.o:
					$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADER)
					$(LIB) $(NAME) $(OBJS)

clean:
					$(RM) $(OBJS) $(B_OBJS)

fclean:		clean
					$(RM) $(NAME)

re:			fclean all

so:			$(OBJS)
					$(CC) -o libft.so $(OBJS) -shared

bonus:		$(OBJS) $(B_OBJS)
					$(LIB) $(NAME) $(OBJS) $(B_OBJS)

.PHONY: 	all clean fclean re
