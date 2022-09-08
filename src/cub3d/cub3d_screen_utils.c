/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_screen_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:35:58 by jhii              #+#    #+#             */
/*   Updated: 2022/09/08 18:52:41 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_out_of_bounds(t_coord coord)
{
	if (coord.x <= 0 || coord.x >= WINDOW_X
		|| coord.y <= 0 || coord.y >= WINDOW_Y)
		return (1);
	return (0);
}

int	check_out_of_screen(t_cub *cub, t_coord coord)
{
	if (coord.x <= cub->screen.x_start || coord.x >= cub->screen.x_end
		|| coord.y <= cub->screen.y_start || coord.y >= cub->screen.y_end)
		return (1);
	return (0);
}

int	is_wall(t_cub *cub, t_vect vect)
{
	t_coord	coord;

	coord.x = (int)(vect.x / TILE_SIZE);
	coord.y = (int)(vect.y / TILE_SIZE);
	if (!check_out_of_bounds(coord))
	{
		if (cub->map.arr[coord.y][coord.x] == '1')
			return (1);
		else if (cub->map.arr[coord.y][coord.x] == 'D'
				&& cub->door_state == CLOSED)
			return (1);
		else
			return (0);
	}
	return (2);
}
