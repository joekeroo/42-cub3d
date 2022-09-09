/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 12:53:42 by jhii              #+#    #+#             */
/*   Updated: 2022/09/09 13:58:56 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	door_check(t_cub *cub)
{
	cub->player.door.x = (int)(cub->player.pos.x / TILE_SIZE);
	cub->player.door.y = (int)(cub->player.pos.y / TILE_SIZE);
	if (cub->map.arr[cub->player.door.y - 1][cub->player.door.x] == 'D'
		|| cub->map.arr[cub->player.door.y - 1][cub->player.door.x] == 'O')
		cub->player.door.y--;
	else if (cub->map.arr[cub->player.door.y + 1][cub->player.door.x] == 'D'
		|| cub->map.arr[cub->player.door.y + 1][cub->player.door.x] == 'O')
		cub->player.door.y++;
	else if (cub->map.arr[cub->player.door.y][cub->player.door.x - 1] == 'D'
		|| cub->map.arr[cub->player.door.y][cub->player.door.x - 1] == 'O')
		cub->player.door.x--;
	else if (cub->map.arr[cub->player.door.y][cub->player.door.x + 1] == 'D'
		|| cub->map.arr[cub->player.door.y][cub->player.door.x + 1] == 'O')
		cub->player.door.x++;
	if (cub->player.door.y == (int)(cub->player.pos.y / TILE_SIZE)
		&& cub->player.door.x == (int)(cub->player.pos.x / TILE_SIZE))
		return (0);
	return (1);
}
