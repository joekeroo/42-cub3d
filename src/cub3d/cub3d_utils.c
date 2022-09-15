/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:00:45 by jhii              #+#    #+#             */
/*   Updated: 2022/09/15 14:24:08 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	destroy_images(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 10)
		mlx_destroy_image(cub->mlx, cub->weapon.frame[i++].ptr);
	mlx_destroy_image(cub->mlx, cub->textures->north.ptr);
	mlx_destroy_image(cub->mlx, cub->textures->south.ptr);
	mlx_destroy_image(cub->mlx, cub->textures->east.ptr);
	mlx_destroy_image(cub->mlx, cub->textures->west.ptr);
	mlx_destroy_image(cub->mlx, cub->img.ptr);
	free(cub->textures);
}

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	free_array(cub->map.arr, cub->map.height);
	destroy_images(cub);
	exit(0);
	return (0);
}

char	**custom_split(char *str)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * count_token(str, 0, 2) + 1);
	while (i < count_token(str, 0, 2))
	{
		k = 0;
		size = count_token(str, j, 1);
		while (str[j] == ' ')
			j++;
		res[i] = malloc(sizeof(char) * size + 1);
		while (k < size)
			res[i][k++] = str[j++];
		res[i][k] = '\0';
		i++;
	}
	res[i] = NULL;
	i = 0;
	return (res);
}

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
		free(array[i++]);
	free(array);
}

void	free_array_null(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}
