/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_error_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:26:52 by jhii              #+#    #+#             */
/*   Updated: 2022/08/30 15:05:15 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	check_filename(char *filename, char	*needle)
{
	int	i;
	int	j;
	int	res;

	j = 0;
	res = 1;
	i = ft_strlen(filename) - 4;
	if (i < 0 || ft_strlen(filename) < 5)
		res = -1;
	while (filename[i])
	{
		if (filename[i++] != needle[j++])
			res = -1;
	}
	if (res < 0)
		ft_putstr_fd("Error: Invalid File Extension.\n", 2);
	return (res);
}

int	filename_error_check(char *filename)
{
	if (check_filename(filename, ".cub") < 0)
		return (1);
	if (!check_file_is_readable(filename))
		return (1);
	return (0);
}
