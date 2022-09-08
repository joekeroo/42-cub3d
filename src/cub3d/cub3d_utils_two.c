/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 18:50:43 by jhii              #+#    #+#             */
/*   Updated: 2022/09/08 19:34:40 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(char *red_char, char *green_char, char *blue_char)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = ft_atoi(red_char);
	green = ft_atoi(green_char);
	blue = ft_atoi(blue_char);
	color = (red / 16) * pow(16, 5);
	color += (red % 16) * pow(16, 4);
	color += (green / 16) * pow(16, 3);
	color += (green % 16) * pow(16, 2);
	color += (blue / 16) * 16;
	color += (blue % 16);
	return (color);
}

void	update_door_frame(t_cub *cub, int type)
{
	if (type == 1)
	{
		cub->frame++;
		cub->map.arr[4][3] = 'O';
	}
	else if (type == 2)
	{
		cub->frame--;
		cub->map.arr[4][3] = 'D';
	}
}
