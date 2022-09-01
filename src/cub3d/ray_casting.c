/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 13:09:13 by jhii              #+#    #+#             */
/*   Updated: 2022/09/01 15:50:08 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	set_line_coord(t_cub *cub, int x)
{
	cub->line[0].x = cub->screen.x_end - x;
	cub->line[1].x = cub->screen.x_end - x;
	cub->line[0].y = cub->ray.line_height / -2
		+ cub->screen.size.y / cub->player.is_crouch;
	cub->line[1].y = cub->ray.line_height / 2
		+ cub->screen.size.y / cub->player.is_crouch;
	if (cub->line[1].y >= cub->screen.y_end)
		cub->line[1].y = cub->screen.y_end;
}

static	double	calculate_wall_hit(t_cub *cub)
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

static	void	set_curr_img(t_cub *cub, t_coord *step)
{
	if (cub->ray.side_hit == 0)
	{
		if (step->x == 1)
			cub->curr_img = &(cub->curr_texture->east);
		else
			cub->curr_img = &(cub->curr_texture->west);
	}
	else
	{
		if (step->y == 1)
			cub->curr_img = &(cub->curr_texture->south);
		else
			cub->curr_img = &(cub->curr_texture->north);
	}
}

static	void	draw_texture(t_cub *cub, t_coord *step)
{
	double	wall_hit;
	t_coord	wall_coord;
	int		wall_index;
	char	*dest;
	t_coord	to_draw;

	to_draw.x = cub->line[0].x;
	to_draw.y = cub->line[0].y;
	wall_hit = calculate_wall_hit(cub);
	while (to_draw.y < cub->line[1].y)
	{
		set_curr_img(cub, step);
		wall_coord.x = (int)(wall_hit * cub->curr_img->size.x);
		wall_coord.y = (int)(((double)(to_draw.y - cub->line[0].y)
					/ (double)cub->ray.line_height) * cub->curr_img->size.x);
		wall_index = wall_coord.x * (cub->curr_img->bpp / 8)
			+ wall_coord.y * cub->curr_img->line_len;
		dest = cub->curr_img->addr + wall_index;
		cub->color = *(unsigned int *)dest;
		if (!check_out_of_screen(cub, to_draw))
			draw_pixel(cub, to_draw);
		to_draw.y++;
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
	t_coord	step;
	t_coord	map_box;

	x = 0;
	while (x < cub->screen.size.x)
	{
		map_box.x = (int)(cub->player.pos.x / TILE_SIZE);
		map_box.y = (int)(cub->player.pos.y / TILE_SIZE);
		calculate_ray_dir(cub, x, cub->screen.size.x);
		calculate_delta_dist(cub);
		calculate_side_dist(cub, &step, &map_box);
		calculate_perp_wall_dist(cub, &step, &map_box);
		cub->ray.line_height = (int)(cub->screen.size.y
				/ cub->ray.perp_wall_dist);
		set_line_coord(cub, x);
		fill_color(cub);
		draw_texture(cub, &step);
		x++;
	}
}
