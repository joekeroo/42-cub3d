/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 17:04:21 by jhii              #+#    #+#             */
/*   Updated: 2022/09/01 13:42:51 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_texture_conditions(int type, int check, int print)
{
	if (type < 4 || !check)
	{
		if (print == 1)
			ft_putstr_fd("Error: Texture Input Incomplete.\n", 2);
		return (1);
	}
	return (0);
}
