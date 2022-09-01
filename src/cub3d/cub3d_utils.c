/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:00:45 by jhii              #+#    #+#             */
/*   Updated: 2022/08/31 18:53:34 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

int	close_window(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->window);
	free_array(cub->map.arr, cub->map.height);
	free(cub->textures);
	exit(0);
	return (0);
}

double	get_distance(t_vect a, t_vect b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
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
