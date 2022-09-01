/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:43 by jhii              #+#    #+#             */
/*   Updated: 2022/08/31 14:42:30 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	check_commas(char *str)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (str[i] == ',')
			total++;
		i++;
	}
	if (total == 2)
		return (1);
	return (0);
}

int	check_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 6)
	{
		free_array(split, i);
		return (0);
	}
	return (i);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static	int	check_comma_spaces(char c, int *len, int *size, int type)
{
	if (c == ',')
	{
		if (*len > 0)
			*size = *size + 1;
		*size = *size + 1;
		if (type == 1 && *len > 0)
			return (*len);
		if (type == 1 && *len == 0)
			return (1);
		*len = 0;
	}
	else
	{
		if (*len > 0)
			*size = *size + 1;
		if (type == 1 && *len > 0)
			return (*len);
		*len = 0;
	}
	return (0);
}

int	count_token(char *str, int i, int type)
{
	int	len;
	int	size;
	int	temp;

	len = 0;
	size = 0;
	temp = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != ',')
			len++;
		else
			temp = check_comma_spaces(str[i], &len, &size, type);
		if (temp > 0)
			return (temp);
		i++;
	}
	if (len > 0)
		size++;
	if (type == 1 && len > 0)
		return (len);
	if (type == 1 && len == 0 && str[i - 1] == ',')
		return (1);
	return (size);
}
