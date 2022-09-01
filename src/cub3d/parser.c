/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:58:54 by jhii              #+#    #+#             */
/*   Updated: 2022/09/01 15:11:14 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_multi_texture(t_cub *cub, char *filename, int fd)
{
	int	i;
	int	temp;

	i = -1;
	cub->lines_read = 0;
	cub->map.texture_count = 0;
	temp = open(filename, O_RDONLY);
	while (!texture_error_check(cub, temp, 0))
		cub->map.texture_count++;
	close(temp);
	if (cub->map.texture_count == 0)
	{
		while (!texture_error_check(cub, temp, 1))
			cub->map.texture_count++;
		return (1);
	}
	cub->lines_read = 0;
	while (++i < cub->map.texture_count)
		texture_error_check(cub, fd, 1);
	return (0);
}

static void	save_texture(t_cub *cub, int fd)
{
	int		i;
	char	*line;
	char	**temp;

	i = 0;
	cub->map.textures = malloc((cub->map.texture_count * 4) * sizeof(char *));
	while (i < cub->map.texture_count * 4)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_replace_space(line, '\t');
		temp = ft_split(line, ' ');
		if (!is_empty_line(line))
			cub->map.textures[i++] = ft_strdup(temp[1]);
		free_array_null(temp);
		free(line);
	}
}

static void	save_color(t_cub *cub, int fd)
{
	int		i;
	int		color;
	char	*line;
	char	**temp;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_replace_space(line, '\t');
		temp = custom_split(line);
		if (!is_empty_line(line))
		{
			color = rgb_to_hex(temp[1], temp[3], temp[5]);
			if (i == 0)
				cub->map.floor_color = color;
			else
				cub->map.ceilling_color = color;
			i++;
		}
		free_array_null(temp);
		free(line);
	}
}

int	parser(t_cub *cub, char *filename)
{
	int	fd;

	if (filename_error_check(filename))
		return (1);
	fd = open(filename, O_RDONLY);
	if (check_multi_texture(cub, filename, fd) || color_error_check(cub, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	save_texture(cub, fd);
	save_color(cub, fd);
	if (map_error_check(cub, fd, filename))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
