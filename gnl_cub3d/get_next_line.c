/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 01:26:38 by bseven            #+#    #+#             */
/*   Updated: 2021/01/26 01:26:46 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_tojoin(t_struct *gnl, char *res)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (gnl->n == -1 && res[++i])
		gnl->guf[i] = res[i];
	if (gnl->n == -1)
		while (gnl->buf[++j])
			gnl->guf[i++] = gnl->buf[j];
	else if (!(i = 0))
		while (res[++gnl->n])
			gnl->guf[i++] = res[gnl->n];
	gnl->guf[i] = '\0';
	return (1);
}

static int	ft_strjoin(t_struct *gnl)
{
	int		i;
	char	*res;

	res = NULL;
	if (gnl->power != ON)
	{
		if (!(gnl->guf = malloc((gnl->j + 1) * sizeof(char))))
			return (0);
		gnl->guf = ft_memcpy_gnl(gnl->guf, gnl->buf, gnl->j + 1);
		gnl->guf[gnl->j] = '\0';
		gnl->power = ON;
		return (1);
	}
	res = gnl->guf;
	i = (gnl->len + (gnl->n == NO ? gnl->j : -(gnl->n + 1))) + 1;
	if (!(gnl->guf = malloc(i * sizeof(char))))
		return (freshka(gnl, res, 0));
	ft_tojoin(gnl, res);
	free(res);
	return (1);
}

static int	strlen_gnl(t_struct *gnl)
{
	int i;

	if (!gnl->power || !gnl->ret)
		return (gnl->ret);
	i = 0;
	while (gnl->guf[i] && gnl->guf[i] != '\n')
		i++;
	gnl->n = gnl->guf[i] ? i : NO;
	while (gnl->guf[i])
		i++;
	gnl->len = i;
	return (gnl->ret);
}

static int	gnl_null(t_struct *gnl, char **line)
{
	if (gnl->power != ON)
	{
		gnl->ret = 1;
		gnl->power = 0;
		gnl->guf = NULL;
	}
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483646 || !line)
		return (0);
	gnl->len = 0;
	gnl->n = 0;
	gnl->j = BUFFER_SIZE;
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static t_struct gnl;

	if (!gnl_null(&gnl, line))
		return (freshka(&gnl, NULL, -1));
	while (strlen_gnl(&gnl))
	{
		gnl.ret = (gnl.j < BUFFER_SIZE && gnl.n == NO) ? 0 : gnl.ret;
		if (gnl.power && gnl.n != NO && !(gnl.guf[gnl.n] = '\0'))
			break ;
		if (gnl.ret && (gnl.n == NO || !gnl.power))
		{
			gnl.j = read(fd, gnl.buf, BUFFER_SIZE);
			if (gnl.j == -1)
				return (freshka(&gnl, NULL, -1));
			gnl.buf[gnl.j] = '\0';
		}
		if (!gnl.power || (gnl.ret && gnl.j && gnl.n == NO))
			if (!ft_strjoin(&gnl))
				return (-1);
	}
	if (!(*line = ft_strdup_gnl(gnl.guf)))
		return (freshka(&gnl, NULL, -1));
	(!gnl.ret && (gnl.power = OFF)) ? free(gnl.guf) : ft_strjoin(&gnl);
	return (gnl.ret);
}
