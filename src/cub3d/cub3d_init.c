/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:25:25 by jhii              #+#    #+#             */
/*   Updated: 2022/09/09 13:42:36 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	t_img	*get_wall_direction(t_cub *cub, int i, int j)
{
	t_img	*img;

	if (j == 0)
		img = &(cub->textures[i].north);
	else if (j == 1)
		img = &(cub->textures[i].south);
	else if (j == 2)
		img = &(cub->textures[i].west);
	else
		img = &(cub->textures[i].east);
	return (img);
}

static	void	texture_init(t_cub *cub)
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
			img = get_wall_direction(cub, i, j);
			img->ptr = mlx_xpm_file_to_image(cub->mlx,
					cub->map.textures[i * 4 + j], &img->size.x, &img->size.y);
			img->addr = mlx_get_data_addr(img->ptr,
					&img->bpp, &img->line_len, &img->endian);
			j++;
		}
		i++;
	}
	cub->curr_texture = &(cub->textures[0]);
	cub->curr_texture_index = 0;
	free_array(cub->map.textures, cub->map.texture_count * 4);
}

static	void	player_dir_init(t_cub *cub)
{
	if (cub->map.player_dir == 'N')
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = -1;
	}
	else if (cub->map.player_dir == 'S')
	{
		cub->player.dir.x = 0;
		cub->player.dir.y = 1;
	}
	else if (cub->map.player_dir == 'E')
	{
		cub->player.dir.x = 1;
		cub->player.dir.y = 0;
	}
	else if (cub->map.player_dir == 'W')
	{
		cub->player.dir.x = -1;
		cub->player.dir.y = 0;
	}
}

static	void	weapon_init(t_cub *cub)
{
	int		i;
	char	*filename;
	char	extension[6];

	i = -1;
	while (++i < 10)
	{
		filename = ft_strdup("weapon/torchlight");
		extension[0] = i + '0';
		extension[1] = '\0';
		ft_strlcat(extension, ".xpm", 10);
		ft_strlcat(filename, extension, 25);
		cub->weapon.frame[i].ptr = mlx_xpm_file_to_image(cub->mlx,
				filename, &cub->weapon.frame[i].size.x,
				&cub->weapon.frame[i].size.y);
		cub->weapon.frame[i].addr = mlx_get_data_addr(cub->weapon.frame[i].ptr,
				&cub->weapon.frame[i].bpp, &cub->weapon.frame[i].line_len,
				&cub->weapon.frame[i].endian);
		free(filename);
	}
}

// N[0, -1] S[0, 1] E[1, 0] W[-1, 0]
void	cub3d_init(t_cub *cub)
{
	player_dir_init(cub);
	cub->player.plane.x = cub->player.dir.y;
	cub->player.plane.y = -cub->player.dir.x;
	cub->player.is_crouch = 2;
	cub->player.pos.x = (cub->map.player_pos.x * TILE_SIZE)
		+ (TILE_SIZE / 2) - (PLAYER_SIZE / 2);
	cub->player.pos.y = (cub->map.player_pos.y * TILE_SIZE)
		+ (TILE_SIZE / 2) - (PLAYER_SIZE / 2);
	cub->player.tile_pos.x = cub->map.player_pos.x;
	cub->player.tile_pos.y = cub->map.player_pos.y;
	cub->mlx = mlx_init();
	cub->window = mlx_new_window(cub->mlx, WINDOW_X, WINDOW_Y, "cub3d");
	cub->img.ptr = mlx_new_image(cub->mlx, WINDOW_X, WINDOW_Y);
	cub->img.addr = mlx_get_data_addr(cub->img.ptr,
			&cub->img.bpp, &cub->img.line_len, &cub->img.endian);
	cub->weapon.status = CLOSED;
	cub->player.door.x = (int)cub->player.pos.x;
	cub->player.door.y = (int)cub->player.pos.y;
	weapon_init(cub);
	texture_init(cub);
}
