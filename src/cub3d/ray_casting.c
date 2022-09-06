/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:09:13 by jhii              #+#    #+#             */
/*   Updated: 2022/09/06 19:14:30 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	set_line_coord(t_cub *cub, int x)
{
	cub->line[0].x = cub->screen.x_start + x;
	cub->line[1].x = cub->screen.x_start + x;
	cub->line[0].y = cub->ray.line_height / -2
		+ cub->screen.size.y / cub->player.is_crouch;
	cub->line[1].y = cub->ray.line_height / 2
		+ cub->screen.size.y / cub->player.is_crouch;
	if (cub->line[1].y >= cub->screen.y_end)
		cub->line[1].y = cub->screen.y_end;
}

static	void	set_curr_img(t_cub *cub, t_coord step)
{
	if (cub->ray.side_hit == 0)
	{
		if (step.x == 1)
			cub->curr_img = &(cub->curr_texture->east);
		else
			cub->curr_img = &(cub->curr_texture->west);
	}
	else
	{
		if (step.y == 1)
			cub->curr_img = &(cub->curr_texture->south);
		else
			cub->curr_img = &(cub->curr_texture->north);
	}
}

static	void	draw_texture(t_cub *cub)
{
	char	*dest;
	double	wall_hit;
	int		wall_index;
	t_coord	wall_coord;
	t_coord	to_draw;

	to_draw.x = cub->line[0].x;
	to_draw.y = cub->line[0].y - 1;
	wall_hit = calculate_wall_hit(cub);
	while (++to_draw.y < cub->line[1].y)
	{
		if (cub->hit_type == 'D')
			wall_coord.x = (int)((wall_hit - cub->limit)
					* cub->curr_img->size.x);
		else
			wall_coord.x = (int)(wall_hit * cub->curr_img->size.x);
		wall_coord.y = (int)(((double)(to_draw.y - cub->line[0].y)
					/ (double)cub->ray.line_height) * cub->curr_img->size.x);
		wall_index = wall_coord.x * (cub->curr_img->bpp / 8)
			+ wall_coord.y * cub->curr_img->line_len;
		dest = cub->curr_img->addr + wall_index;
		cub->color = *(unsigned int *)dest;
		if (!check_out_of_screen(cub, to_draw))
			draw_pixel(cub, to_draw);
	}
}

void	fill_color(t_cub *cub)
{
	int		i;
	t_coord	to_draw;

	i = cub->screen.y_start;
	to_draw.x = cub->line[0].x;
	cub->color = cub->map.ceilling_color;
	while (i < cub->line[0].y)
	{
		to_draw.y = i;
		draw_pixel(cub, to_draw);
		i++;
	}
	i = cub->line[1].y + 1;
	cub->color = cub->map.floor_color;
	while (i <= cub->screen.y_end)
	{
		to_draw.y = i;
		draw_pixel(cub, to_draw);
		i++;
	}
}

void	render_screen(t_cub *cub)
{
	int		x;
	double	camera_x;
	t_coord	step;

	x = 0;
	while (x < cub->screen.size.x)
	{
		camera_x = 2.0 * x / (double)cub->screen.size.x - 1.0;
		cub->ray.dir.x = cub->player.dir.x - cub->player.plane.x * camera_x;
		cub->ray.dir.y = cub->player.dir.y - cub->player.plane.y * camera_x;
		calculate_delta_dist(cub);
		calculate_side_dist(cub, &step);
		calculate_perp_wall_dist(cub, step, cub->player.tile_pos);
		cub->ray.line_height = (int)(cub->screen.size.y
				/ cub->ray.perp_wall_dist);
		set_line_coord(cub, x);
		fill_color(cub);
		set_curr_img(cub, step);
		draw_texture(cub);
		x++;
	}
}
