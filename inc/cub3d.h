/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:23 by jhii              #+#    #+#             */
/*   Updated: 2022/09/15 14:16:23 by jhii             ###   ########.fr       */
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

# define MINIMAP_SIZE	15
# define FOV_TURN_ANGLE	3
# define MOVE_GAP		3
# define PLAYER_SIZE	5
# define TILE_SIZE		16
# define WINDOW_X		2048
# define WINDOW_Y		1024
# define TORCH_FPS 		1
# define TORCH_FOV 		4.5
# define QRAD 			1.5708
# define RAD 			0.0174533

enum {
	YELLOW = 0xFFFF00,
	WHITE = 0xFFFFFF,
	RED = 0xFF0000,
	GRAY = 0x808080,
	LIME = 0x32CD32,
	BLACK = 0x000000
};

enum {
	WALL = 1,
	DOOR = 2
};

enum {
	Q = 12,
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	E = 14,
	C = 8,
	T = 17,
	H = 4,
	ESC = 53,
	LEFT = 123,
	RIGHT = 124
};

enum {
	CLOSED = 0,
	CLOSING = 1,
	OPENED = 2,
	OPENING = 3,
	POS_UP = 1,
	POS_DOWN = 2,
	POS_LEFT = 3,
	POS_RIGHT = 4
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
	char	player_dir;
	t_coord	player_pos;
	int		texture_count;
	int		floor_color;
	int		ceilling_color;
	int		width;
	int		height;
	int		pixel_width;
	int		pixel_height;
}				t_map;

typedef struct s_screen
{
	t_coord	size;
	t_vect	player_pos;
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
	t_coord	door;
	t_coord	tile_pos;
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

typedef struct s_weapon
{
	int		status;
	t_img	frame[10];
}				t_weapon;

typedef struct s_cub
{
	t_img		img;
	t_ray		ray;
	t_map		map;
	t_plyr		player;
	t_weapon	weapon;
	t_coord		line[2];
	t_screen	screen;
	t_texture	*textures;
	t_texture	*curr_texture;
	t_img		*curr_img;
	int			curr_texture_index;
	int			color;
	int			lines_read;
	int			frame;
	int			door_state;
	int			mouse_state;
	double		limit;
	char		hit_type;
	void		*mlx;
	void		*window;
}				t_cub;

// Parsing and Error checking functions
int		filename_error_check(char *filename);
int		check_texture_conditions(int type, int check, int print);
int		texture_error_check(t_cub *cub, int fd, int print);
int		check_commas(char *str);
int		check_split(char **split);
int		count_token(char *str, int i, int type);
int		is_digit(char *str);
int		parser(t_cub *cub, char *filename);
int		color_error_check(t_cub *cub, int fd);
int		check_map(t_cub *cub);
int		check_player(t_cub *cub);
int		check_valid_map(t_cub *cub);
int		map_error_check(t_cub *cub, int fd, char *filename);
void	map_init(t_cub *cub, char *filename);
void	print_map_array(t_cub *cub);

// Rendering functions
void	render_map(t_cub *cub);
void	render_weapon(t_cub *cub);

// Parsing Utility functions
int		ft_strcmp(char *a, char *b);
int		is_empty_line(char *str);
char	*remove_nl(char *str);
char	**custom_split(char *str);
void	ft_replace_space(char *str, char c);

// Main cub3d functions
void	cub3d(t_cub *cub);
void	cub3d_init(t_cub *cub);

// Drawing functions
void	draw_pixel(t_cub *cub, t_coord coord);
void	draw_square(t_cub *cub, int x, int y, int size);
void	draw_line(t_cub *cub);

// Utilities functions
char	*get_next_line(int fd);
int		close_window(t_cub *cub);
int		is_wall(t_cub *cub, t_vect vect);
int		check_file_is_readable(char *filename);
int		check_out_of_bounds(t_coord coord);
int		check_out_of_screen(t_cub *cub, t_coord coord);
int		rgb_to_hex(char *red, char *green, char *blue);
void	free_array_null(char **array);
void	free_array(char **array, int size);
void	update_door_frame(t_cub *cub, int type);

// Ray casting functions
void	render_screen(t_cub *cub);
void	calculate_delta_dist(t_cub *cub);
void	calculate_side_dist(t_cub *cub, t_coord *step);
void	calculate_perp_wall_dist(t_cub *cub, t_coord step, t_coord ray_tile);
double	calculate_wall_hit(t_cub *cub);

// Door Handling fuctions
int		door_check(t_cub *cub);

// Player control functions
int		mouse_controls(t_cub *cub);
int		controls(int key, t_cub *cub);

#endif
