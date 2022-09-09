/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:54:53 by jhii              #+#    #+#             */
/*   Updated: 2022/09/09 14:21:58 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_map_condition(t_cub *cub, t_coord map_tile, int type)
{
	if (type == WALL)
	{
		if (map_tile.y >= 0 && map_tile.y < cub->map.height
			&& map_tile.x >= 0 && map_tile.x < cub->map.width
			&& cub->map.arr[map_tile.y][map_tile.x] == '1')
			return (1);
	}
	else if (type == DOOR)
	{
		if (map_tile.y >= 0 && map_tile.y < cub->map.height
			&& map_tile.x >= 0 && map_tile.x < cub->map.width
			&& (cub->map.arr[map_tile.y][map_tile.x] == 'D'
			|| cub->map.arr[map_tile.y][map_tile.x] == 'O'))
			return (1);
	}
	return (0);
}

static	void	draw_map_tile(t_cub *cub, t_coord tile, int type)
{
	t_coord	to_draw;

	if (type == WALL)
	{
		to_draw.x = tile.x * TILE_SIZE
			- (((int)cub->player.pos.x % TILE_SIZE) - TILE_SIZE / 2);
		to_draw.y = tile.y * TILE_SIZE
			- (((int)cub->player.pos.y % TILE_SIZE) - TILE_SIZE / 2);
		cub->color = BLACK;
		draw_square(cub, to_draw.x, to_draw.y, TILE_SIZE);
		cub->color = WHITE;
		draw_square(cub, to_draw.x + 1, to_draw.y + 1, TILE_SIZE - 2);
	}
	else if (type == DOOR)
	{
		to_draw.x = tile.x * TILE_SIZE
			- (((int)cub->player.pos.x % TILE_SIZE) - TILE_SIZE / 2);
		to_draw.y = tile.y * TILE_SIZE
			- (((int)cub->player.pos.y % TILE_SIZE) - TILE_SIZE / 2);
		cub->color = BLACK;
		draw_square(cub, to_draw.x, to_draw.y, TILE_SIZE);
		cub->color = LIME;
		draw_square(cub, to_draw.x + 1, to_draw.y + 1, TILE_SIZE - 2);
	}
}

void	render_map(t_cub *cub)
{
	t_coord	tile;
	t_coord	map_tile;

	tile.y = 0;
	while (tile.y < MINIMAP_SIZE)
	{
		tile.x = 0;
		map_tile.y = cub->player.tile_pos.y - 7 + tile.y;
		while (tile.x < MINIMAP_SIZE)
		{
			map_tile.x = cub->player.tile_pos.x - 7 + tile.x;
			if (check_map_condition(cub, map_tile, WALL))
				draw_map_tile(cub, tile, WALL);
			else if (check_map_condition(cub, map_tile, DOOR))
				draw_map_tile(cub, tile, DOOR);
			tile.x++;
		}
		tile.y++;
	}
}
