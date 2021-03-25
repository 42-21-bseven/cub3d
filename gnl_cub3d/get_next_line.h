/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:26:54 by bseven            #+#    #+#             */
/*   Updated: 2021/01/26 01:27:07 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define NO -1
# define ON 777
# define OFF 666
# define BUFFER_SIZE 512

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_struct
{
	char		*guf;
	char		buf[(BUFFER_SIZE > 2147483646 || BUFFER_SIZE <= 0) ?\
	1 : (BUFFER_SIZE + 1)];
	int			len;
	int			n;
	int			j;
	int			power;
	int			ret;
}				t_struct;

int				get_next_line(int fd, char **line);
char			*ft_memcpy_gnl(char *dest, char *src, size_t n);
char			*ft_strdup_gnl(char *s);
size_t			ft_strlen_gnl(char *s);
int				freshka(t_struct *gnl, char *res, int retka);

#endif
