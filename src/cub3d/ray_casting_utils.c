/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:41 by jhii              #+#    #+#             */
/*   Updated: 2022/09/08 19:15:20 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_delta_dist(t_cub *cub)
{
	if (cub->ray.dir.x == 0)
		cub->ray.delta_dist.x = 1e30;
	else
		cub->ray.delta_dist.x = fabs(1.0 / cub->ray.dir.x);
	if (cub->ray.dir.y == 0)
		cub->ray.delta_dist.y = 1e30;
	else
		cub->ray.delta_dist.y = fabs(1.0 / cub->ray.dir.y);
}

double	calculate_wall_hit(t_cub *cub)
{
	double	wall_hit;

	if (cub->ray.side_hit == 0)
	{
		wall_hit = (cub->player.pos.y + cub->ray.perp_wall_dist
				* (cub->ray.dir.y * TILE_SIZE));
	}
	else
	{
		wall_hit = (cub->player.pos.x + cub->ray.perp_wall_dist
				* (cub->ray.dir.x * TILE_SIZE));
	}
	wall_hit = (((int)wall_hit % TILE_SIZE)
			+ (wall_hit - floor(wall_hit))) / TILE_SIZE;
	return (wall_hit);
}

void	calculate_side_dist(t_cub *cub, t_coord *step)
{
	if (cub->ray.dir.x < 0)
	{
		step->x = -1;
		cub->ray.side_dist.x = cub->ray.delta_dist.x
			* ((cub->player.pos.x / TILE_SIZE) - cub->player.tile_pos.x);
	}
	else
	{
		step->x = 1;
		cub->ray.side_dist.x = cub->ray.delta_dist.x
			* (cub->player.tile_pos.x + 1.0 - (cub->player.pos.x / TILE_SIZE));
	}
	if (cub->ray.dir.y < 0)
	{
		step->y = -1;
		cub->ray.side_dist.y = cub->ray.delta_dist.y
			* ((cub->player.pos.y / TILE_SIZE) - cub->player.tile_pos.y);
	}
	else
	{
		step->y = 1;
		cub->ray.side_dist.y = cub->ray.delta_dist.y
			* (cub->player.tile_pos.y + 1.0 - (cub->player.pos.y / TILE_SIZE));
	}
}

static	void	check_door_status(t_cub *cub, t_coord ray_tile)
{
	double	wall_hit;

	if (cub->map.arr[ray_tile.y][ray_tile.x] == 'D'
		|| cub->map.arr[ray_tile.y][ray_tile.x] == 'O')
	{
		if (cub->ray.side_hit == 0)
			cub->ray.perp_wall_dist = cub->ray.side_dist.x
				- cub->ray.delta_dist.x;
		else
			cub->ray.perp_wall_dist = cub->ray.side_dist.y
				- cub->ray.delta_dist.y;
		wall_hit = calculate_wall_hit(cub);
		cub->limit = (double)cub->frame * 0.1;
		if (cub->door_state == CLOSED)
			cub->hit_type = 'D';
		if (wall_hit >= cub->limit)
			cub->hit_type = 'D';
	}
}

void	calculate_perp_wall_dist(t_cub *cub, t_coord step, t_coord ray_tile)
{
	cub->hit_type = '0';
	while (cub->hit_type == '0')
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			ray_tile.x += step.x;
			cub->ray.side_hit = 0;
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			ray_tile.y += step.y;
			cub->ray.side_hit = 1;
		}
		if (cub->map.arr[ray_tile.y][ray_tile.x] == '1')
			cub->hit_type = '1';
		check_door_status(cub, ray_tile);
	}
	if (cub->ray.side_hit == 0)
		cub->ray.perp_wall_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
	else
		cub->ray.perp_wall_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
}
