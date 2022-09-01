/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 15:47:59 by jhii              #+#    #+#             */
/*   Updated: 2022/09/01 14:57:47 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_texture_source(char *filename)
{
	if (!check_file_is_readable(filename))
		return (0);
	return (1);
}

static	int	check_texture_direction(char *str, int type, int print)
{
	if (type == 0)
	{
		if (ft_strcmp(str, "NO"))
			return (1);
	}
	else if (type == 1)
	{
		if (ft_strcmp(str, "SO"))
			return (1);
	}
	else if (type == 2)
	{
		if (ft_strcmp(str, "WE"))
			return (1);
	}
	else if (type == 3)
	{
		if (ft_strcmp(str, "EA"))
			return (1);
	}
	if (print == 1)
		ft_putstr_fd("Error: Texture Syntax Error.\n", 2);
	return (0);
}

static	int	check_texture_line(char **split, int type, int print)
{
	if (!check_texture_direction(split[0], type, print))
		return (0);
	if (!check_texture_source(split[1]))
		return (0);
	return (1);
}

static	int	check_texture_format(char *str, int type, int print)
{
	int		i;
	int		check;
	char	**split;

	i = 0;
	check = 0;
	ft_replace_space(str, '\t');
	split = ft_split(str, ' ');
	while (split[i])
		i++;
	if (i != 2)
	{
		if (i != 0)
			free_array(split, i);
		return (0);
	}
	check = check_texture_line(split, type, print);
	free_array(split, i);
	if (!check)
		return (0);
	return (1);
}

int	texture_error_check(t_cub *cub, int fd, int print)
{
	int		type;
	int		check;
	char	*line;

	type = 0;
	check = 1;
	while (check && type < 4)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cub->lines_read++;
		if (!is_empty_line(line))
			check = check_texture_format(line, type++, print);
		free(line);
	}
	return (check_texture_conditions(type, check, print));
}
