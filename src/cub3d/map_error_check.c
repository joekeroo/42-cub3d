/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:40:46 by jhii              #+#    #+#             */
/*   Updated: 2022/09/06 18:50:32 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	fill_spaces(char **str, int start, int len)
{
	while (start < len)
		(*str)[start++] = ' ';
}

static	void	init_map_arr(t_cub *cub, int fd)
{
	int		i;
	char	*line;

	i = 0;
	cub->map.width = 0;
	cub->map.height = 2;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((int)ft_strlen(line) > cub->map.width)
			cub->map.width = ft_strlen(line);
		free(line);
		cub->map.height++;
	}
	cub->map.width += 2;
	cub->map.arr = malloc(cub->map.height * sizeof(char *));
	while (i < cub->map.height)
	{	
		cub->map.arr[i] = malloc((cub->map.width + 1) * sizeof(char));
		cub->map.arr[i++][cub->map.width] = '\0';
	}
}

static	void	fill_map_arr(t_cub *cub, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_replace_space(line, '\t');
		if (cub->lines_read)
			cub->lines_read--;
		else if (!is_empty_line(line))
		{
			j = 0;
			cub->map.arr[i][j] = ' ';
			while (++j < (int)ft_strlen(line) + 1)
				cub->map.arr[i][j] = line[j - 1];
			fill_spaces(&(cub->map.arr[i++]), j, cub->map.width);
		}
		else if (i > 0)
			fill_spaces(&(cub->map.arr[i++]), 0, cub->map.width);
		free(line);
	}
}

int	map_error_check(t_cub *cub, int fd, char *filename)
{
	init_map_arr(cub, fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	fill_spaces(&(cub->map.arr[0]), 0, cub->map.width);
	fill_map_arr(cub, fd);
	fill_spaces(&(cub->map.arr[cub->map.height - 1]), 0, cub->map.width);
	if (check_valid_map(cub) || check_map(cub) || check_player(cub))
	{
		ft_putstr_fd("Error: Map Input Error.\n", 2);
		free_array(cub->map.arr, cub->map.height);
		return (1);
	}
	cub->screen.size.x = WINDOW_X;
	cub->screen.size.y = WINDOW_Y;
	cub->screen.player_pos.x = (MINIMAP_SIZE * TILE_SIZE - PLAYER_SIZE) / 2;
	cub->screen.player_pos.y = (MINIMAP_SIZE * TILE_SIZE - PLAYER_SIZE) / 2;
	cub->screen.x_start = 0;
	cub->screen.y_start = 0;
	cub->screen.x_end = WINDOW_X;
	cub->screen.y_end = WINDOW_Y;
	return (0);
}
