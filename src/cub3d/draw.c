/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:02:01 by jhii              #+#    #+#             */
/*   Updated: 2022/08/24 18:23:28 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_pixel(t_cub *cub, t_coord coord)
{
	int		dist;
	char	*dest;

	if (!check_out_of_bounds(coord))
	{
		dist = coord.x * (cub->img.bpp / 8) + coord.y * cub->img.line_len;
		dest = cub->img.addr + dist;
		*(unsigned int *)dest = cub->color;
	}
}

void	draw_square(t_cub *cub, int x, int y, int size)
{
	t_coord	coord;
	int		temp;
	int		x_size;
	int		y_size;

	temp = x;
	x_size = x + size;
	y_size = y + size;
	while (y < y_size)
	{
		x = temp;
		while (x < x_size)
		{
			coord.x = x;
			coord.y = y;
			draw_pixel(cub, coord);
			x++;
		}
		y++;
	}
}

static void	draw_line_low(t_cub *cub, int dx, int dy)
{
	int		d;
	int		dir;
	t_coord	coord;

	dir = 1 - (2 * (dy < 0));
	if (dy < 0)
		dy *= -1;
	d = (2 * dy) - dx;
	coord = cub->line[0];
	while (coord.x < cub->line[1].x)
	{
		draw_pixel(cub, coord);
		if (d > 0)
		{
			coord.y += dir;
			d -= 2 * dx;
		}
		d += 2 * dy;
		coord.x++;
	}
}

static void	draw_line_high(t_cub *cub, int dx, int dy)
{
	int		d;
	int		dir;
	t_coord	coord;

	dir = 1 - (2 * (dx < 0));
	if (dx < 0)
		dx *= -1;
	d = (2 * dx) - dy;
	coord = cub->line[0];
	while (coord.y < cub->line[1].y)
	{
		draw_pixel(cub, coord);
		if (d > 0)
		{
			coord.x += dir;
			d -= 2 * dy;
		}
		d += 2 * dx;
		coord.y++;
	}
}

void	draw_line(t_cub *cub)
{
	int	dx;
	int	dy;
	int	temp;

	dx = cub->line[1].x - cub->line[0].x;
	dy = cub->line[1].y - cub->line[0].y;
	if ((cub->line[0].x > cub->line[1].x && abs(dx) > abs(dy))
		|| (cub->line[0].y > cub->line[1].y && abs(dx) <= abs(dy)))
	{
		temp = cub->line[0].x;
		cub->line[0].x = cub->line[1].x;
		cub->line[1].x = temp;
		temp = cub->line[0].y;
		cub->line[0].y = cub->line[1].y;
		cub->line[1].y = temp;
	}
	dx = cub->line[1].x - cub->line[0].x;
	dy = cub->line[1].y - cub->line[0].y;
	if (abs(dx) > abs(dy))
		draw_line_low(cub, dx, dy);
	else
		draw_line_high(cub, dx, dy);
}
