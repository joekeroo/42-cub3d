/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:32:32 by hyun-zhe          #+#    #+#             */
/*   Updated: 2022/09/15 10:23:03 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	init_dir(t_cub *cub, t_coord *dir)
{
	if (cub->map.player_dir == 'N')
	{
		dir->x = 0;
		dir->y = -1;
	}
	else if (cub->map.player_dir == 'S')
	{
		dir->x = 0;
		dir->y = 1;
	}
	else if (cub->map.player_dir == 'E')
	{
		dir->x = 1;
		dir->y = 0;
	}
	else if (cub->map.player_dir == 'W')
	{
		dir->x = -1;
		dir->y = 0;
	}
}

int	mouse_controls(t_cub *cub)
{
	t_coord	mouse;
	t_coord	dir;
	double	ratio;
	double	angle;

	init_dir(cub, &dir);
	mlx_mouse_get_pos(cub->window, &mouse.x, &mouse.y);
	if (mouse.x == WINDOW_X - 1)
		mlx_mouse_move(cub->window, 0, WINDOW_Y / 2);
	else if (mouse.x == 0)
		mlx_mouse_move(cub->window, WINDOW_X, WINDOW_Y / 2);
	else
		mlx_mouse_move(cub->window, mouse.x, WINDOW_Y / 2);
	ratio = mouse.x / (double)WINDOW_X;
	angle = (M_PI * ratio * 2) - M_PI;
	cub->player.dir.x = dir.x * cos(angle) - dir.y * sin(angle);
	cub->player.dir.y = dir.y * cos(angle) + dir.x * sin(angle);
	cub->player.plane.x = cub->player.dir.y;
	cub->player.plane.y = -cub->player.dir.x;
	return (0);
}
