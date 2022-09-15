/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:16 by jhii              #+#    #+#             */
/*   Updated: 2022/09/15 13:39:51 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	render_player(t_cub *cub)
{
	if (cub->door_state == OPENING && cub->limit <= 1.0)
		update_door_frame(cub, 1);
	else if (cub->door_state == CLOSING && cub->frame > 0)
		update_door_frame(cub, 2);
	else if (cub->frame == 0)
		cub->door_state = CLOSED;
	if (cub->mouse_state == OPENED)
		mouse_controls(cub);
	mlx_destroy_image(cub->mlx, cub->img.ptr);
	cub->img.ptr = mlx_new_image(cub->mlx, WINDOW_X, WINDOW_Y);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	render_screen(cub);
	cub->color = BLACK;
	draw_square(cub, cub->screen.player_pos.x,
		cub->screen.player_pos.y, PLAYER_SIZE);
	render_map(cub);
	cub->color = RED;
	draw_square(cub, cub->screen.player_pos.x + 1,
		cub->screen.player_pos.y + 1, PLAYER_SIZE - 2);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.ptr, 0, 0);
	render_weapon(cub);
	return (0);
}

void	cub3d(t_cub *cub)
{
	cub3d_init(cub);
	cub->frame = 0;
	mlx_mouse_hide();
	mlx_mouse_move(cub->window, WINDOW_X / 2, WINDOW_Y / 2);
	mlx_hook(cub->window, 2, 1L << 0, controls, cub);
	mlx_hook(cub->window, 17, 1L << 1, close_window, cub);
	mlx_loop_hook(cub->mlx, render_player, cub);
	mlx_loop(cub->mlx);
}
