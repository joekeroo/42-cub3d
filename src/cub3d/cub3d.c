/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:16 by jhii              #+#    #+#             */
/*   Updated: 2022/09/06 19:08:24 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_map_condition(t_cub *cub, t_coord map_tile)
{
	if (map_tile.y >= 0 && map_tile.y < cub->map.height
		&& map_tile.x >= 0 && map_tile.x < cub->map.width
		&& (cub->map.arr[map_tile.y][map_tile.x] == '1'
		|| cub->map.arr[map_tile.y][map_tile.x] == 'D'))
		return (1);
	return (0);
}

static	void	draw_map_tile(t_cub *cub, t_coord tile)
{
	t_coord	to_draw;

	to_draw.x = tile.x * TILE_SIZE
		- (((int)cub->player.pos.x % TILE_SIZE) - TILE_SIZE / 2);
	to_draw.y = tile.y * TILE_SIZE
		- (((int)cub->player.pos.y % TILE_SIZE) - TILE_SIZE / 2);
	cub->color = BLACK;
	draw_square(cub, to_draw.x, to_draw.y, TILE_SIZE);
	cub->color = WHITE;
	draw_square(cub, to_draw.x + 1, to_draw.y + 1, TILE_SIZE - 2);
}

void	render_map_2d(t_cub *cub)
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
			if (check_map_condition(cub, map_tile))
				draw_map_tile(cub, tile);
			tile.x++;
		}
		tile.y++;
	}
}

int	render_player(t_cub *cub)
{
	if (cub->door_state == 1 && cub->limit <= 1.0)
		cub->frame++;
	else if (cub->door_state == 2 && cub->frame > 0)
		cub->frame--;
	else if (cub->frame == 0)
		cub->door_state = 0;
	mlx_destroy_image(cub->mlx, cub->img.ptr);
	cub->img.ptr = mlx_new_image(cub->mlx, WINDOW_X, WINDOW_Y);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	render_screen(cub);
	cub->color = BLACK;
	draw_square(cub, cub->screen.player_pos.x,
		cub->screen.player_pos.y, PLAYER_SIZE);
	cub->color = RED;
	draw_square(cub, cub->screen.player_pos.x + 1,
		cub->screen.player_pos.y + 1, PLAYER_SIZE - 2);
	render_map_2d(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.ptr, 0, 0);
	return (0);
}

void	cub3d(t_cub *cub)
{
	cub3d_init(cub);
	cub->frame = 0;
	mlx_hook(cub->window, 2, 1L << 0, controls, cub);
	mlx_hook(cub->window, 17, 1L << 1, close_window, cub);
	mlx_loop_hook(cub->mlx, render_player, cub);
	mlx_loop(cub->mlx);
}
