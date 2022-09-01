/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:01:28 by jhii              #+#    #+#             */
/*   Updated: 2022/08/30 16:46:27 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_strcmp(char *a, char *b)
{
	int	i;

	i = 0;
	if (ft_strlen(a) != ft_strlen(b))
		return (0);
	while (a[i])
	{
		if (a[i] != b[i])
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

int	check_file_is_readable(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": File Not Readable.\n", 2);
		return (0);
	}
	close(fd);
	return (1);
}

char	*remove_nl(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = -1;
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	res = malloc(sizeof(char) * len + 1);
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

void	ft_replace_space(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			str[i] = ' ';
		i++;
	}
}
