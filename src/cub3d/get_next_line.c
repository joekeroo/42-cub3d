/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhii <jhii@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 11:39:08 by jhii              #+#    #+#             */
/*   Updated: 2022/08/20 11:40:12 by jhii             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	ft_getnl(char *str)
{
	int		i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i + 1);
}

static char	*ft_check(int fd, char **storage, int size, char *res)
{
	if (*storage[0] == '\0' || size < 0 || fd < 0)
	{
		free(*storage);
		*storage = NULL;
	}
	return (res);
}

static char	*ft_combine(int fd, char **storage)
{
	char	buffer[2];
	char	*temp;
	char	*res;
	int		size;

	res = NULL;
	size = 0;
	while (size >= 0 && ft_getnl(*storage) == 0)
	{
		size = read(fd, buffer, 1);
		buffer[size] = '\0';
		if (buffer[0] == '\0' || size == 0)
		{
			if (*storage[0] != '\0')
				res = *storage;
			else
				free(*storage);
			*storage = NULL;
			return (res);
		}
		temp = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = temp;
	}
	return (ft_check(fd, &*storage, size, res));
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*temp;
	char		*res;

	res = NULL;
	if (!storage)
	{
		storage = malloc(sizeof(char *) * 1);
		storage[0] = '\0';
	}
	res = ft_combine(fd, &storage);
	if (res != NULL)
		return (res);
	else
		if (storage == NULL)
			return (res);
	if (storage[0] != '\0' && ft_getnl(storage) > 0)
	{
		res = ft_substr(storage, 0, ft_getnl(storage));
		temp = ft_substr(storage, ft_getnl(storage), ft_strlen(storage));
		if (storage[0] != '\0')
			free(storage);
		storage = temp;
	}
	return (res);
}
