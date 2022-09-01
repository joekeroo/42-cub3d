/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_screen_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:35:58 by jhii              #+#    #+#             */
/*   Updated: 2022/08/30 10:37:21 by jhii             ###   ########.fr       */
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
	int		dist;
	char	*dest;
	t_coord	coord;

	coord.x = (int)(vect.x);
	coord.y = (int)(vect.y);
	if (!check_out_of_bounds(coord))
	{
		dist = coord.x * (cub->img.bpp / 8) + coord.y * cub->img.line_len;
		dest = cub->img.addr + dist;
		if (*(unsigned int *)dest == WHITE)
			return (1);
		else
			return (0);
	}
	return (2);
}
