/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:51:05 by jhii              #+#    #+#             */
/*   Updated: 2022/09/01 12:51:33 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_valid_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.arr[i][j] != '0' && cub->map.arr[i][j] != '1' &&
				cub->map.arr[i][j] != 'N' && cub->map.arr[i][j] != 'S' &&
				cub->map.arr[i][j] != 'E' && cub->map.arr[i][j] != 'W' &&
				cub->map.arr[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < cub->map.height)
	{
		j = 0;
		while (j < cub->map.width)
		{
			if (cub->map.arr[i][j] == '0')
			{
				if (cub->map.arr[i - 1][j] == ' ' ||
					cub->map.arr[i + 1][j] == ' ' ||
					cub->map.arr[i][j - 1] == ' ' ||
					cub->map.arr[i][j + 1] == ' ')
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_player(t_cub *cub)
{
	int	i;
	int	j;
	int	player_count;

	i = -1;
	player_count = 0;
	while (++i < cub->map.height)
	{
		j = -1;
		while (++j < cub->map.width)
		{
			if (cub->map.arr[i][j] == 'N' || cub->map.arr[i][j] == 'S' ||
				cub->map.arr[i][j] == 'E' || cub->map.arr[i][j] == 'W')
			{
				cub->map.player_dir = cub->map.arr[i][j];
				cub->map.player_pos.x = j;
				cub->map.player_pos.y = i;
				player_count++;
			}
		}
	}
	if (player_count == 1)
		return (0);
	ft_putstr_fd("Error: Too Many Players in Map.\n", 2);
	return (1);
}
