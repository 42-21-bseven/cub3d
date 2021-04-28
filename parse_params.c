/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bseven <bseven@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 03:57:25 by bseven            #+#    #+#             */
/*   Updated: 2021/04/28 03:57:28 by bseven           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_param(t_tab *tab, char *line)
{
	if (ft_strlen(line) == 1)
		return (-1);
	while (*line)
	{
		if (*line == 32)
			line++;
		else if (*line == 'R')
			return (parse_rsltn(tab, &line));
		else if (*line == 'F' || *line == 'C')
			return (check_place(tab, &line));
		else if (*line == 'N' || *line == 'W' || *line == 'E')
			return (snd_lit_check(tab, line));
		else if (*line == 'S')
		{
			if (*(line + 1) == 'O' || (*(line + 1) == 32))
				return (snd_lit_check(tab, line));
			else
				return (-1 + (tab->check_flag =
						put_error("\nERROR!\nInvalid Path.\n")));
		}
		else
			return (-1 + (tab->check_flag =
					put_error("\nERROR!\nInvalid Path.\n")));
	}
	return (1);
}

int	parse_rsltn(t_tab *tab, char **str)
{
	char *err;

	err = "\nERROR!\nInvalid Resolution.\n";
	if (*(++(*str)) != 32 || tab->flags.rsltn == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	if (ft_isdigit(*(++(*str))) == 1)
		tab->prms.rsltn.x = ft_atoi(str);
	else
		return (-1 + (tab->check_flag = put_error(err)));
	if (**str == 32 && ft_isdigit(*(++(*str))) == 1)
		tab->prms.rsltn.y = ft_atoi(str);
	else
		return (-1 + (tab->check_flag = put_error(err)));
	while (*str && **str == 32)
		(*str)++;
	if (**str || (tab->prms.rsltn.x < 1 || tab->prms.rsltn.y < 1))
		return (-1 + (tab->check_flag = put_error(err)));
	return (tab->flags.rsltn = 1);
}

int	check_place(t_tab *tab, char **str)
{
	if (**str == 'F')
		return (parse_clrs_f(tab, str));
	if (**str == 'C')
		return (parse_clrs_c(tab, str));
	return (0);
}

int	parse_clrs_f(t_tab *tab, char **str)
{
	char *err;

	err = "\nERROR!\nFloor Color Invalid.\n";
	if (*(++(*str)) != 32 || tab->flags.floor == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	if (ft_isdigit(*(++(*str))) == 1)
		tab->prms.clrs.floor_r = ft_atoi(str);
	if (char_check(str) == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	tab->prms.clrs.floor_g = ft_atoi(str);
	if (char_check(str) == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	tab->prms.clrs.floor_b = ft_atoi(str);
	if (**str != '\0')
		if ((**str != 32) || (*(++(*str)) != 0))
			return (-1 + (tab->check_flag = put_error(err)));
	if (range_clr(tab->prms.clrs.floor_r, tab->prms.clrs.floor_g,
				tab->prms.clrs.floor_b))
		return (-1 + (tab->check_flag = put_error(err)));
	return (tab->flags.floor = 1);
}

int	parse_clrs_c(t_tab *tab, char **str)
{
	char *err;

	err = "\nERROR!\nCeil Color Invalid.\n";
	if (*(++(*str)) != 32 || tab->flags.ceil == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	if (ft_isdigit(*(++(*str))) == 1)
		tab->prms.clrs.ceil_r = ft_atoi(str);
	if (char_check(str) == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	tab->prms.clrs.ceil_g = ft_atoi(str);
	if (char_check(str) == 1)
		return (-1 + (tab->check_flag = put_error(err)));
	tab->prms.clrs.ceil_b = ft_atoi(str);
	if (**str != '\0')
		if ((**str != 32) || (*(++(*str)) != 0))
			return (-1 + (tab->check_flag = put_error(err)));
	if (range_clr(tab->prms.clrs.ceil_r, tab->prms.clrs.ceil_g,
				tab->prms.clrs.ceil_b))
		return (-1 + (tab->check_flag = put_error(err)));
	return (tab->flags.ceil = 1);
}
