/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:21:16 by jhii              #+#    #+#             */
/*   Updated: 2022/08/29 18:27:10 by jhii             ###   ########.fr       */
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
	cast_ray(cub);
	mlx_put_image_to_window(cub->mlx, cub->window, cub->img.ptr, 0, 0);
	return (0);
}

void	texture_init(t_cub *cub)
{
	int		i;
	int		j;
	t_img	*img;

	i = 0;
	cub->textures = malloc(cub->map.texture_count * sizeof(t_texture));
	while (i < cub->map.texture_count)
	{
		j = 0;
		while (j < 4)
		{
			if (j == 0)
				img = &(cub->textures[i].north);
			else if (j == 1)
				img = &(cub->textures[i].south);
			else if (j == 2)
				img = &(cub->textures[i].west);
			else
				img = &(cub->textures[i].east);
			img->ptr = mlx_xpm_file_to_image(cub->mlx, cub->map.textures[i * 4 + j], &img->size.x, &img->size.y);
			img->addr = mlx_get_data_addr(img->ptr, &img->bpp, &img->line_len, &img->endian);
			j++;
		}
		i++;
	}
	cub->curr_texture = &(cub->textures[0]);
	cub->curr_texture_index = 0;
	free_array(cub->map.textures, cub->map.texture_count * 4);
}

// N[0, -1] S[0, 1] E[1, 0] W[-1, 0]
void	cub3d_init(t_cub *cub)
{
	cub->player.dir.x = 0;
	cub->player.dir.y = -1;
	cub->player.plane.x = (0.75 * cub->player.dir.y);
	cub->player.plane.y = -(0.75 * cub->player.dir.x);
	cub->player.is_crouch = 2;
	cub->player.pos.x = (10 * TILE_SIZE) + (TILE_SIZE / 2) - PLAYER_SIZE;
	cub->player.pos.y = (3 * TILE_SIZE) + (TILE_SIZE / 2) - PLAYER_SIZE;
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	cub->img.ptr = mlx_new_image(cub->mlx, WINDOW_X, WINDOW_Y);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	texture_init(cub);
}

void	cub3d(char *filename)
{
	t_cub	cub;

	map_init(&cub, filename);
	cub.map.textures = malloc(8 * sizeof(char *));
	cub.map.textures[0] = ft_strdup("textures/quake_wall_1.xpm");
	cub.map.textures[1]= ft_strdup("textures/quake_wall_2.xpm");
	cub.map.textures[2] = ft_strdup("textures/quake_wall_3.xpm");
	cub.map.textures[3] = ft_strdup("textures/quake_wall_3.xpm");
	cub.map.textures[4] = ft_strdup("textures/42_single_switch.xpm");
	cub.map.textures[5]= ft_strdup("textures/42_switches.xpm");
	cub.map.textures[6] = ft_strdup("textures/42_wall.xpm");
	cub.map.textures[7] = ft_strdup("textures/42_wall.xpm");
	cub.map.texture_count = 2;
	cub3d_init(&cub);
	mlx_hook(cub.window, 2, 1L << 0, controls, &cub);
	mlx_hook(cub.window, 17, 1L << 1, close_window, &cub);
	mlx_loop_hook(cub.mlx, render_player, &cub);
	mlx_loop(cub.mlx);
}
