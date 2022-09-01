/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:16 by jhii              #+#    #+#             */
/*   Updated: 2022/08/31 18:51:27 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_map_2d(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.arr[i][j] == '1')
			{
				cub->color = WHITE;
				draw_square(cub, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE);
			}
			j++;
		}
		i++;
	}
}

int	render_player(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.ptr);
	cub->img.ptr = mlx_new_image(cub->mlx, WINDOW_X, WINDOW_Y);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	render_map_2d(cub);
	cub->color = RED;
	draw_square(cub, cub->player.pos.x, cub->player.pos.y, PLAYER_SIZE);
	render_map_2d(cub);
	cub->color = YELLOW;
	render_screen(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.ptr, 0, 0);
	return (0);
}

void	cub3d(t_cub *cub)
{
	cub3d_init(cub);
	mlx_hook(cub->window, 2, 1L << 0, controls, cub);
	mlx_hook(cub->window, 17, 1L << 1, close_window, cub);
	mlx_loop_hook(cub->mlx, render_player, cub);
	mlx_loop(cub->mlx);
}
