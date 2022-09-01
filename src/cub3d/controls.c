/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:45:02 by jhii              #+#    #+#             */
/*   Updated: 2022/08/30 10:24:49 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	vertical_movement(int key, t_cub *cub)
{
	t_vect	vect;

	if (key == W)
	{
		vect.x = cub->player.pos.x + (cub->player.dir.x * (MOVE_GAP + 0.1));
		vect.y = cub->player.pos.y + (cub->player.dir.y * (MOVE_GAP + 0.1));
		if (!is_wall(cub, vect))
		{
			cub->player.pos.x = vect.x;
			cub->player.pos.y = vect.y;
		}
	}
	else if (key == S)
	{
		vect.x = cub->player.pos.x - (cub->player.dir.x * (MOVE_GAP + 0.1));
		vect.y = cub->player.pos.y - (cub->player.dir.y * (MOVE_GAP + 0.1));
		if (!is_wall(cub, vect))
		{
			cub->player.pos.x = vect.x;
			cub->player.pos.y = vect.y;
		}
	}
	return (0);
}

static	int	horizontal_movement(int key, t_cub *cub)
{
	t_vect	vect;
	t_vect	dir;

	if (key == A)
	{
		dir.x = cub->player.dir.x * cos(-QRAD) - cub->player.dir.y * sin(-QRAD);
		dir.y = cub->player.dir.y * cos(-QRAD) + cub->player.dir.x * sin(-QRAD);
	}
	else if (key == D)
	{
		dir.x = cub->player.dir.x * cos(QRAD) - cub->player.dir.y * sin(QRAD);
		dir.y = cub->player.dir.y * cos(QRAD) + cub->player.dir.x * sin(QRAD);
	}
	if (key == A || key == D)
	{
		vect.x = cub->player.pos.x + (dir.x * (MOVE_GAP + 0.1));
		vect.y = cub->player.pos.y + (dir.y * (MOVE_GAP + 0.1));
		if (!is_wall(cub, vect))
		{
			cub->player.pos.x = vect.x;
			cub->player.pos.y = vect.y;
		}
	}
	return (0);
}

static	int	view_controls(int key, t_cub *cub)
{
	double	rad;
	double	old_dir_x;
	double	old_plane_x;

	rad = 0.0;
	if (key == LEFT)
		rad = -RAD;
	else if (key == RIGHT)
		rad = RAD;
	if (key == LEFT || key == RIGHT)
	{
		old_dir_x = cub->player.dir.x;
		cub->player.dir.x = cub->player.dir.x * cos(rad * FOV_TURN_ANGLE)
			- cub->player.dir.y * sin(rad * FOV_TURN_ANGLE);
		cub->player.dir.y = cub->player.dir.y * cos(rad * FOV_TURN_ANGLE)
			+ old_dir_x * sin(rad * FOV_TURN_ANGLE);
		old_plane_x = cub->player.plane.x;
		cub->player.plane.x = cub->player.plane.x * cos(rad * FOV_TURN_ANGLE)
			- cub->player.plane.y * sin(rad * FOV_TURN_ANGLE);
		cub->player.plane.y = cub->player.plane.y * cos(rad * FOV_TURN_ANGLE)
			+ old_plane_x * sin(rad * FOV_TURN_ANGLE);
	}
	return (0);
}

int	controls(int key, t_cub *cub)
{
	if (key == ESC)
		close_window(cub);
	else if (key == C)
	{
		if (cub->player.is_crouch == 2)
			cub->player.is_crouch = 4;
		else
			cub->player.is_crouch = 2;
	}
	else if (key == T)
	{
		cub->curr_texture_index = ++cub->curr_texture_index
			% cub->map.texture_count;
		cub->curr_texture = &(cub->textures[cub->curr_texture_index]);
	}
	view_controls(key, cub);
	vertical_movement(key, cub);
	horizontal_movement(key, cub);
	return (0);
}
