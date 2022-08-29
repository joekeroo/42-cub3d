/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:23 by jhii              #+#    #+#             */
/*   Updated: 2022/08/29 18:24:49 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define BORDER			20
# define FOV_TURN_ANGLE	3
# define MOVE_GAP		3
# define PLAYER_SIZE	5
# define TILE_SIZE		16
# define WINDOW_X		2048
# define WINDOW_Y		1024
# define QRAD 			1.5708
# define RAD 			0.0174533

enum {
	YELLOW = 0xFFFF00,
	WHITE = 0xFFFFFF,
	RED = 0xFF0000
};

enum {
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	C = 8,
	T = 17,
	ESC = 53,
	LEFT = 123,
	RIGHT = 124
};

typedef struct s_coord
{
	int	x;
	int	y;
}				t_coord;

typedef struct s_vect
{
	double	x;
	double	y;
}				t_vect;

typedef struct s_map
{
	char	**arr;
	char	**textures;
	int		texture_count;
	int		width;
	int		height;
	int		pixel_width;
	int		pixel_height;
}				t_map;

typedef struct s_screen
{
	t_coord	size;
	int		x_start;
	int		y_start;
	int		x_end;
	int		y_end;
}				t_screen;

typedef struct s_plyr
{
	t_vect	dir;
	t_vect	pos;
	t_vect	plane;
	int		is_crouch;
}				t_plyr;

typedef struct s_ray
{
	t_vect	dir;
	t_vect	side_dist;
	t_vect	delta_dist;
	int		side_hit;
	int		line_height;
	double	perp_wall_dist;
}				t_ray;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_coord	size;
}				t_img;

typedef struct s_texture
{
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
}				t_texture;

typedef struct s_cub
{
	t_img		img;
	t_ray		ray;
	t_map		map;
	t_plyr		player;
	t_coord		line[2];
	t_screen	screen;
	t_texture	*textures;
	t_texture	*curr_texture;
	t_img		*curr_img;
	int			curr_texture_index;
	int			color;
	void		*mlx;
	void		*window;
}				t_cub;

// Main cub3d function
void	cub3d(char *filename);

// Map initializing functions
void	print_map_array(t_cub *cub);
void	map_init(t_cub *cub, char *filename);

// Drawing functions
void	draw_pixel(t_cub *cub, t_coord coord);
void	draw_square(t_cub *cub, int x, int y, int size);
void	draw_line(t_cub *cub);

// Utilities functions
char	*get_next_line(int fd);
int		close_window(t_cub *cub);
int		check_out_of_bounds(t_coord coord);
int		check_out_of_screen(t_cub *cub, t_coord coord);
int		is_wall(t_cub *cub, t_vect vect);
void	free_array(char **array, int size);
double	get_distance(t_vect a, t_vect b);

// Ray casting functions
void	cast_ray(t_cub *cub);
void	calculate_ray_dir(t_cub *cub, int x, int width);
void	calculate_delta_dist(t_cub *cub);
void	calculate_side_dist(t_cub *cub, t_coord *step, t_coord *map);
void	calculate_perp_wall_dist(t_cub *cub, t_coord *stp, t_coord *map);

// Player control functions
int		controls(int key, t_cub *cub);

#endif
