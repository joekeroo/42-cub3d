/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:10:24 by jhii              #+#    #+#             */
/*   Updated: 2022/08/24 16:58:05 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	map_size_init(t_cub *cub, char *filename)
{
	int		fd;
	char	*line;

	cub->map.width = 0;
	cub->map.height = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (cub->map.width == 0)
		{
			if (line[ft_strlen(line) - 1] == '\n')
				cub->map.width = ft_strlen(line) - 1;
		}
		free(line);
		line = get_next_line(fd);
		cub->map.height++;
	}
	cub->map.pixel_width = cub->map.width * TILE_SIZE;
	cub->map.pixel_height = cub->map.height * TILE_SIZE;
	close(fd);
}

static	char	*remove_nl(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	res = malloc(sizeof(char) * len + 1);
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

void	print_map_array(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.height)
	{
		printf("%s", cub->map.arr[i++]);
		if (cub->map.arr[i])
			printf("\n");
	}
	printf("\n");
}

void	map_init(t_cub *cub, char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	*temp;

	i = 0;
	map_size_init(cub, filename);
	fd = open(filename, O_RDONLY);
	cub->map.arr = malloc(sizeof(char *) * cub->map.height);
	line = get_next_line(fd);
	while (line)
	{
		temp = remove_nl(line);
		cub->map.arr[i++] = ft_strdup(temp);
		free(temp);
		free(line);
		line = get_next_line(fd);
	}
	cub->screen.size.x = WINDOW_X - cub->map.pixel_width - (BORDER * 2);
	cub->screen.size.y = WINDOW_Y - (BORDER * 2);
	cub->screen.x_start = cub->map.pixel_width + BORDER;
	cub->screen.y_start = BORDER;
	cub->screen.x_end = WINDOW_X - BORDER;
	cub->screen.y_end = WINDOW_Y - BORDER;
	close(fd);
}
