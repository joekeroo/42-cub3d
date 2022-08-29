/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:41 by jhii              #+#    #+#             */
/*   Updated: 2022/08/29 16:08:04 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	calculate_ray_dir(t_cub *cub, int x, int width)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)width - 1.0;
	cub->ray.dir.x = cub->player.dir.x + cub->player.plane.x * camera_x;
	cub->ray.dir.y = cub->player.dir.y + cub->player.plane.y * camera_x;
}

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

void	calculate_side_dist(t_cub *cub, t_coord *step, t_coord *map)
{
	if (cub->ray.dir.x < 0)
	{
		step->x = -1;
		cub->ray.side_dist.x = ((cub->player.pos.x / TILE_SIZE) - map->x)
			* cub->ray.delta_dist.x;
	}
	else
	{
		step->x = 1;
		cub->ray.side_dist.x = (map->x + 1.0 - (cub->player.pos.x / TILE_SIZE))
			* cub->ray.delta_dist.x;
	}
	if (cub->ray.dir.y < 0)
	{
		step->y = -1;
		cub->ray.side_dist.y = ((cub->player.pos.y / TILE_SIZE) - map->y)
			* cub->ray.delta_dist.y;
	}
	else
	{
		step->y = 1;
		cub->ray.side_dist.y = (map->y + 1.0 - (cub->player.pos.y / TILE_SIZE))
			* cub->ray.delta_dist.y;
	}
}

void	calculate_perp_wall_dist(t_cub *cub, t_coord *stp, t_coord *map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cub->ray.side_dist.x < cub->ray.side_dist.y)
		{
			cub->ray.side_dist.x += cub->ray.delta_dist.x;
			map->x += stp->x;
			cub->ray.side_hit = 0;
		}
		else
		{
			cub->ray.side_dist.y += cub->ray.delta_dist.y;
			map->y += stp->y;
			cub->ray.side_hit = 1;
		}
		if (cub->map.arr[map->y][map->x] == '1')
			hit = 1;
	}
	if (cub->ray.side_hit == 0)
		cub->ray.perp_wall_dist = cub->ray.side_dist.x - cub->ray.delta_dist.x;
	else
		cub->ray.perp_wall_dist = cub->ray.side_dist.y - cub->ray.delta_dist.y;
}
