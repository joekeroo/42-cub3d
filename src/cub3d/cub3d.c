#include "cub3d.h"

# define RAD 0.0174533

int	check_out_of_bounds(t_cub *cub, t_coord coord)
{
	if (coord.x <= 0 || coord.x >= cub->x_size ||
		coord.y <= 0 || coord.y >= cub->y_size)
		return (1);
	return (0);
}

void	draw_pixel(t_cub *cub, t_coord coord)
{
	int		dist;
	char	*dest;

	if (!check_out_of_bounds(cub, coord))
	{
		dist = coord.x * (cub->img.bbp / 8) + coord.y * cub->img.line_len;
		dest = cub->img.addr + dist;
		*(unsigned int *)dest = cub->color;
	}
}

void	draw_square(t_cub *cub, int x, int y, int size, int border)
{
	t_coord	coord;

	for (int i = y; i < y + size; i++)
	{
		for (int j = x; j < x + size; j++)
		{
			coord.x = j + border;
			coord.y = i + border;
			draw_pixel(cub, coord);
		}
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
		// draw_square(cub, coord.x, coord.y, 2, 0);
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
		// draw_square(cub, coord.x, coord.y, 2, 0);
		if (d > 0)
		{
			coord.x += dir;
			d -= 2 * dy;
		}
		d += 2 * dx;
		coord.y++;
	}
}

static void	draw_line(t_cub *cub)
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

void	render_map_2d(t_cub *cub)
{
	char	map[10][12] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '0', '0', 'N', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			if (map[i][j] == '1')
			{
				draw_square(cub, j * 66, i * 66, 64, 2);
			}
			else if (map[i][j] == '0')
			{
				// draw floor
			}
		}
	}
}

void	cast_rays(t_cub *cub, int deg)
{
	float	a;
	(void)deg;

	cub->line[0] = cub->player.pos;
	cub->line[0].x += 4;
	cub->line[0].y += 4;
	// a = cub->player.a - RAD * 30;
	a = cub->player.a;
	if (a < 0)
		a += 2 * M_PI;
	else if (a > 2 * M_PI)
		a -= 2 * M_PI;
	for (int i = 0; i < 10; i++)
	{
		printf("player_direction %f\n", a);
		printf("i %d\n", i);
		cub->line[1].x = cub->line[0].x;
		cub->line[1].y = cub->line[0].y;
		cub->line[1].x += cos(a) * 100;
		cub->line[1].y += sin(a) * 100;
		// cub->line[1].x = abs(cub->line[1].x);
		// cub->line[1].y = abs(cub->line[1].y);
		printf("x: %d, y: %d\n", cub->line[1].x, cub->line[1].y);
		if (cub->line[1].x < 0)
			// cub->line[1].x += cub->line[0].x;
			cub->line[1].x = 0;
		if (cub->line[1].y < 0)
			cub->line[1].y = 0;
		draw_line(cub);
		a += RAD;
		if (a < 0)
			a += 2 * M_PI;
		else if (a > 2 * M_PI)
			a -= 2 * M_PI;
	}
	// exit(0);
}

int	render_player(t_cub *cub)
{
	mlx_destroy_image(cub->mlx, cub->img.img);
	cub->img.img = mlx_new_image(cub->mlx, cub->x_size, cub->y_size);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bbp, &cub->img.line_len, &cub->img.endian);
	cub->color = 0xFFFFFF;
	render_map_2d(cub);
	cub->color = 0xFFFF00;
	draw_square(cub, cub->player.pos.x, cub->player.pos.y, 8, 0);
	cast_rays(cub, 90);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.img, 0, 0);
	return (0);
}

int	controls(int key, t_cub *cub)
{
	if (key == 13)
		cub->player.pos.y -= 8;
	else if (key == 0)
		cub->player.pos.x -= 8;
	else if (key == 1)
		cub->player.pos.y += 8;
	else if (key == 2)
		cub->player.pos.x += 8;
	else if (key == 123)
	{
		cub->player.a -= 0.1;
		if (cub->player.a < 0)
			cub->player.a += 2 * M_PI;
		cub->player.dist.x = cos(cub->player.a) * 25;
		cub->player.dist.y = sin(cub->player.a) * 25;
	}
	else if (key == 124)
	{
		cub->player.a += 0.1;
		if (cub->player.a > 2 * M_PI)
			cub->player.a -= 2 * M_PI;
		cub->player.dist.x = cos(cub->player.a) * 25;
		cub->player.dist.y = sin(cub->player.a) * 25;
	}
	return (0);
}

void	cub3d()
{
	t_cub	cub;

	cub.x_size = 66 * 12 + 2;
	cub.y_size = 66 * 10 + 2;
	cub.player.pos.x = 4 * 66 + 28;
	cub.player.pos.y = 3 * 66 + 28;
	// cub.player.a = 3 * M_PI_2;
	cub.player.a = 0;
	cub.player.dist.x = cos(cub.player.a) * 25;
	cub.player.dist.y = sin(cub.player.a) * 25;
	cub.mlx = mlx_init();
	cub.window = mlx_new_window(cub.mlx, cub.x_size, cub.y_size, "cub3d");
	cub.img.img = mlx_new_image(cub.mlx, cub.x_size, cub.y_size);
	cub.img.addr = mlx_get_data_addr(cub.img.img, &cub.img.bbp, &cub.img.line_len, &cub.img.endian);
	mlx_put_image_to_window(cub.mlx, cub.window, cub.img.img, 0, 0);
	mlx_key_hook(cub.window, controls, &cub);
	mlx_loop_hook(cub.mlx, render_player, &cub);
	mlx_loop(cub.mlx);	
}