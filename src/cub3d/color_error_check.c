/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_error_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:18:51 by jhii              #+#    #+#             */
/*   Updated: 2022/08/31 18:19:32 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_color_type(char **split, int len, int type)
{
	if (!ft_strcmp(split[2], ",") || !ft_strcmp(split[4], ","))
	{
		free_array(split, len);
		return (0);
	}
	if (type == 0)
	{
		if (ft_strcmp(split[0], "F"))
			return (1);
	}
	else if (type == 1)
	{
		if (ft_strcmp(split[0], "C"))
			return (1);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(split[0], 2);
	ft_putstr_fd(": Texture Syntax Error.\n", 2);
	free_array(split, len);
	return (0);
}

static	int	check_digit(char **split, int len)
{
	int	i;
	int	temp;
	int	count;

	i = 0;
	count = 0;
	if (is_digit(split[1]) && is_digit(split[3]) && is_digit(split[5]))
	{
		while (i < len)
		{
			if (i % 2 == 1)
			{
				temp = ft_atoi(split[i]);
				if (temp >= 1 && temp <= 255)
					count++;
			}
			i++;
		}
		if (count == 3)
			return (1);
	}
	ft_putstr_fd("Error: Invalid RGB Values.\n", 2);
	free_array(split, len);
	return (0);
}

static	int	check_color_format(char *str, int type)
{
	int		len;
	char	**split;

	if (!check_commas(str))
		return (0);
	ft_replace_space(str, '\t');
	split = custom_split(str);
	len = check_split(split);
	if (len == 0)
		return (0);
	if (!check_color_type(split, len, type))
		return (0);
	if (!check_digit(split, len))
		return (0);
	free_array(split, len);
	return (1);
}

int	color_error_check(t_cub *cub, int fd)
{
	int		type;
	int		check;
	char	*line;

	type = 0;
	check = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cub->lines_read++;
		if (!is_empty_line(line))
			check = check_color_format(line, type++);
		free(line);
		if (!check || type > 1)
			break ;
	}
	if (type < 2 || !check)
	{
		ft_putstr_fd("Error: RGB Values Input Error.\n", 2);
		return (1);
	}
	return (0);
}
