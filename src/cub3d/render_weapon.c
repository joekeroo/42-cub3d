/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 16:52:31 by jhii              #+#    #+#             */
/*   Updated: 2022/09/15 14:13:35 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	check_condition(t_cub *cub, int curr)
{
	mlx_put_image_to_window(cub->mlx, cub->window,
		cub->weapon.frame[curr].ptr, WINDOW_X - cub->weapon.frame[curr].size.x,
		WINDOW_Y - cub->weapon.frame[curr].size.y);
}

static	void	check_last_condition(t_cub *cub, int *frame, int curr, int type)
{
	mlx_put_image_to_window(cub->mlx, cub->window,
		cub->weapon.frame[curr].ptr, WINDOW_X - cub->weapon.frame[curr].size.x,
		WINDOW_Y - cub->weapon.frame[curr].size.y);
	cub->weapon.status = type;
	*frame = 0;
}

static	void	render_opening(t_cub *cub, int *frame)
{
	if (cub->weapon.status == OPENING)
	{
		*frame = *frame + 1;
		if (*frame < 1 * TORCH_FPS)
			check_condition(cub, 9);
		else if (*frame < 2 * TORCH_FPS)
			check_condition(cub, 8);
		else if (*frame < 3 * TORCH_FPS)
			check_condition(cub, 7);
		else if (*frame < 4 * TORCH_FPS)
			check_condition(cub, 6);
		else if (*frame < 5 * TORCH_FPS)
			check_condition(cub, 5);
		else if (*frame < 6 * TORCH_FPS)
			check_condition(cub, 4);
		else if (*frame < 7 * TORCH_FPS)
			check_condition(cub, 3);
		else if (*frame < 8 * TORCH_FPS)
			check_condition(cub, 2);
		else if (*frame < 9 * TORCH_FPS)
			check_condition(cub, 1);
		else if (*frame < 10 * TORCH_FPS)
			check_last_condition(cub, frame, 0, OPENED);
	}
}

static	void	render_closing(t_cub *cub, int *frame)
{
	if (cub->weapon.status == CLOSING)
	{
		*frame = *frame + 1;
		if (*frame < 1 * TORCH_FPS)
			check_condition(cub, 0);
		else if (*frame < 2 * TORCH_FPS)
			check_condition(cub, 1);
		else if (*frame < 3 * TORCH_FPS)
			check_condition(cub, 2);
		else if (*frame < 4 * TORCH_FPS)
			check_condition(cub, 3);
		else if (*frame < 5 * TORCH_FPS)
			check_condition(cub, 4);
		else if (*frame < 6 * TORCH_FPS)
			check_condition(cub, 5);
		else if (*frame < 7 * TORCH_FPS)
			check_condition(cub, 6);
		else if (*frame < 8 * TORCH_FPS)
			check_condition(cub, 7);
		else if (*frame < 9 * TORCH_FPS)
			check_condition(cub, 8);
		else if (*frame < 10 * TORCH_FPS)
			check_last_condition(cub, frame, 9, CLOSED);
	}
}

void	render_weapon(t_cub *cub)
{
	static int	frame;

	if (cub->weapon.status == OPENED)
		mlx_put_image_to_window(cub->mlx, cub->window,
			cub->weapon.frame[0].ptr, WINDOW_X - cub->weapon.frame[0].size.x,
			WINDOW_Y - cub->weapon.frame[0].size.y);
	render_opening(cub, &frame);
	render_closing(cub, &frame);
}
