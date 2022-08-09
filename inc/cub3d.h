#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

// typedef struct	s_map
// {
// 	char	map[5][6];
// }				t_map;

typedef struct	s_plyr
{
	t_coord	pos;
	t_coord	dist;
	float	a;
}				t_plyr;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_cub
{
	// t_map	map;
	t_plyr	player;
	t_img	img;
	void	*mlx;
	void	*window;
	int		x_size;
	int		y_size;
	t_coord	line[2];
	int		color;
}				t_cub;

void	cub3d();

#endif